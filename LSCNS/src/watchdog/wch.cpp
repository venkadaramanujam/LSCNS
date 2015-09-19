
#include "wch.hpp"

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int Watcher::init(char *dirpath, EventRecv *ev)
{
  /*creating the INOTIFY instance*/
  fd = inotify_init();

  /*checking for error*/
  if ( fd < 0 ) {
    perror( "inotify_init" );
    return APP_ERR;
  }

  /*adding the “/tmp” directory into watch list. Here, the suggestion is to validate the existence of the directory before adding into monitoring list.*/
  wd = inotify_add_watch( fd, dirpath, IN_CREATE | IN_DELETE | IN_MODIFY);

  if(wd < 0)
  {
	  perror("inotify_add_watch");
	  return APP_ERR;
  }

  return APP_OK;
}

int Watcher::watch( )
{
  int length, i = 0;
  char buffer[EVENT_BUF_LEN];

  /*read to determine the event change happens on “/tmp” directory. Actually this read blocks until the change event occurs*/ 

  while(1)
  {
  length = read( fd, buffer, EVENT_BUF_LEN );

  /*checking for error*/
  if ( length < 0 ) {
    perror( "read" );
  }  

  /*actually read return the list of change events happens. Here, read the change event one by one and process it accordingly.*/
  while ( i < length ) {     struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];     if ( event->len ) {
      if ( event->mask & IN_CREATE ) {
        if ( event->mask & IN_ISDIR ) {
          printf( "New directory %s created.\n", event->name );
        }
        else {
          printf( "New file %s created.\n", event->name );
        }
      }
      else if ( event->mask & IN_DELETE ) {
        if ( event->mask & IN_ISDIR ) {
          printf( "Directory %s deleted.\n", event->name );
        }
        else {
          printf( "File %s deleted.\n", event->name );
        }
      }
      else if ( event->mask & IN_MODIFY ) {
        if ( event->mask & IN_ISDIR ) {
          printf( "Directory %s modified.\n", event->name );
        }
        else {
          printf( "File %s modified.\n", event->name );
        }
      }
    }
    i += EVENT_SIZE + event->len;
  }
  }
}

int Watcher::stop( )
{

  /*removing the “/tmp” directory from the watch list.*/
   inotify_rm_watch( fd, wd );

  /*closing the INOTIFY instance*/
   close( fd );
}
