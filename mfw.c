
#include <ctype.h>
#include <stdlib.h>
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

static struct inout_flag;



/* read in command line agruments */
int main(int argc, char **argv){

  int c;
  while (1)
    {
      static struct option long_options[] =
        {
          /* These options set a flag. */
          {"in", 	no_argument, 		&inout_flag, 1},
          {"out", no_argument, 			&inout_flag, 0},
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"proto",     required_argument,       0, 'a'},
          {"action",  required_argument,       0, 'b'},         
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "ab:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

       
        case 'a':
          printf ("option -a with value `%s'\n", optarg);
          break;

        case 'b':
          printf ("option -b with value `%s'\n", optarg);
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

  /* Instead of reporting ‘--verbose’
     and ‘--brief’ as they are encountered,
     we report the final status resulting from them. */
  if (inout_flag)
    puts ("in flag is set");

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }

  exit (0);
}