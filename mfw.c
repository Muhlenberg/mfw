#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include "rule.h"


static int inout_flag;

FILE *file;


int
main (int argc, char **argv)
{
  int c;
  struct mfw_rule Rule = {
    ALLOW,
    IN,
    -1,
    0,
    0
  };
  int tcp = 6;
  int udp = 17;
  int all = -1;

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
          {"proto",     required_argument, 0, 'c'},
          {"action",    required_argument, 0, 'd'},
          {"srcport",     required_argument, 0, 'f'},
          {"destport",    required_argument, 0, 'g'},
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
          /*Do we need to be able to read in order to print all of the rules??*/
          break;

        case 'b': /*delete, requires rule # */
          printf ("option delete with value `%s'\n", optarg);
          /*do this */
          break;

        case 'c': /* proto type, TCP, UDP, ALL */
          printf ("option proto with value `%s'\n", optarg);
          /* sets rule.protocol to respective protocol values */
          if (strcpy(optarg, "TCP") == 0){
            Rule.protocol = (intptr_t)tcp;
          }
          if (strcpy(optarg, "UDP") == 0){
            Rule.protocol = (intptr_t)udp;
          }
          if (strcpy(optarg, "ALL") == 0){
            Rule.protocol = (intptr_t)all;
          }
          break;

        case 'd': /* action (ALLOW/DENY) */
          if (strcpy(optarg, "ALLOW") == 0){
            Rule.action = ALLOW;
          }
          if (strcpy(optarg, "DENY")== 0){
            Rule.action = DENY;
          }
          /* else.... */
          break;

        case 'f': /*source ip */
          printf ("source ip with value `%s'\n", optarg);
          Rule.srcport = (intptr_t)optarg;
          break;

        case 'g': /* destination ip */
          printf("destination ip with value `%s'\n", optarg);
          Rule.destport = (intptr_t)optarg;
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
    Rule.direction = IN;
  else
    Rule.direction = OUT; /* */

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }

  /* size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) */

  file = fopen( "/proc/mfwrules", "w");
  fwrite (&Rule, sizeof(Rule), 1, file);
  fclose(file);

  exit (0);
}
