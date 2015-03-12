/*#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h> */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define PROCFS_MAX_SIZE			1024
#define PROCFS_NAME				"buffer1k"

/*not sure what is actually needed of this */
static struct proc_dir_entry *Our_Proc_File;
static char procfs_buffer[PROCFS_MAX_SIZE];
static unsigned long procfs_buffer_size = 0;

/** For now
/*somehow write arguements to proc file *
int procfile_write(struct file *file, const char *buffer, unsigned long count,
					void *data)
{
	/* get buffer size *
	procfs_buffer_size = count;
	if (procfs_buffer_size > PROCFS_MAX_SIZE) {
		procfs_buffer_size = PROCFS_MAX_SIZE;
	}

	/*write data to the buffer *
	if (copy_from_user(procfs_buffer, buffer, procfs_buffer_size) ) {
		return -EFAULT;
	}

	return procfs_buffer_size;
}
**/

/* read in command line agruments */
int main(int argc, char **argv){

	/*copying an example of getOpt */

	int aflag = 0;
	int bflag = 0;
	char *cvalue = NULL;
	int index;
	int c;

	opterr = 0;

	while ((c= getopt (argc, argv, "abc:")) != -1)
		switch (c)
	{
		case 'a':
			aflag = 1;
			break;
      	case 'b':
       		bflag = 1;
        	break;
      	case 'c':
        	cvalue = optarg;
        	break;
      	case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }

      printf ("aflag= %d, bflag = %d, cvalue = %s\n",
      			aflag, bflag, cvalue);

      for (index = optind; index <argc; index++)
      	printf ("Non-opion argument %s\n", argv[index]);
      return 0;
	}


	/* old testing command line 
	printf("argc = %d\n", argc);
	for (i=0; i<argc; i++)
		printf("arg[%d] = \"%s\"\n", i, argv[i]);
		*/
}