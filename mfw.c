#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "rule.h"


static int inout_flag;

struct mfw_rule *rule;



/* size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) */


int
main (int argc, char **argv)
{
  int c;
  struct mfw_rule Rule;

  while (1)
    {
      static struct option long_options[] =
        {
          /* These options set a flag. */
          {"in", no_argument,       &inout_flag, 1},
          {"out",   no_argument,       &inout_flag, 0},
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"print",     no_argument,       0, 'a'},
          {"delete",    required_argument, 0, 'b'},
          {"proto",     required_argument, 0, 'd'},
          {"action",    required_argument, 0, 'c'},
          {"srcip",     required_argument, 0, 'f'},
          {"destip",    required_argument, 0, 'g'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "ab:c:d:e:f:g:",
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

        case 'a': /* print */
          puts ("option -a\n");
          /*Wait do I need to be able to read in order to print all of the rules??*/
          break;

        case 'b': /*delete, requires rule # */
          printf ("option -b with value `%s'\n", optarg);
          /*do this */
          break;

        case 'c': /* proto type, TCP, UDP, ALL */
          printf ("option -c with value `%s'\n", optarg);
          Rule.protocol = optarg;
          break;

        case 'd': /* action (ALLOW/DENY) */
          printf ("option -d with value `%s'\n", optarg);
          Rule.action = optarg;
          break;

        case 'f': /*source ip */
          printf ("option -f with value `%s'\n", optarg);
          Rule.srcport = optarg;
          break;

        case 'g': /* destination ip */
          printf("option -g with value `%s'\n", optarg);
          Rule.destport = optarg;
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

  /*  */
  if (inout_flag)
    /*puts ("in flag is set");*/
    Rule.direction = "IN";
  else 
    Rule.direction = "OUT"; /* */

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }

  /* add some print statements to test, then work on */
    /*http://www.tutorialspoint.com/cprogramming/c_structures.htm */

  exit (0);
}

