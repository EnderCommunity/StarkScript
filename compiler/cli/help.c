/**
 *
 *  Manage the help console message
 *
**/


// Define the help catalog function
void helpCatalog(){

    // Print the help catalog
    consoleLog(

    // You must never add any whitespace in this part of this file
"%sUsage%s: Stark [options]\n\
%sOptions%s:\n\
    %s--help%s                   View the help catalog\n\
                                 (This option will prevent the compiler from receiving any more command line arguments, and any already-passed arguments will be ignored)\n\
    %s--input%s <path>           Pass the path of your input file\n\
    %s--output%s <directory>     Pass the output directory of your compiled program\n\
                                 (Defaults to the input file directory)\n\
    %s--name%s <string>          Pass the name of the output executable\n\
                                 (Defaults to \"EXECUTABLE\")\n\
    %s--no-gray%s                Prevent debug console messages from being colored in gray\n\
                                 (Note that this flag will take effect only after it's detection, so you may see some gray text!)\n\
    %s--save-temps%s             Keep intermediate files\n\
    %s--save-temps-c%s           Keep C intermediate files\n\
    %s--gcc%s                    Runs the \"gcc -v\" command\n\
    %s--no-colors%s              Set all the text in the console to be white\n\
    %s--cat%s                    Have a very emotional cat report all the console messages to you!\n\
    %s--debug%s                  Show debug messages\n\
    %s-h%s <path>                Same as --help\n\
    %s-i%s <path>                Same as --input\n\
    %s-o%s <directory>           Same as --output\n\
    %s-n%s <string>              Same as --name\n\n\
For bug reporting, please visit: %sissues/\n",

    // The "Usage" title
    CONSOLE_COLOR_CYAN, CONSOLE_COLOR_RESET,

    // The "Options" title
    CONSOLE_COLOR_CYAN, CONSOLE_COLOR_RESET,

    // The options/flags
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_RED, CONSOLE_COLOR_RESET, // Colour the `--save-temps-c` flag with red to indicate
                                            // that it's an incomplete flag!
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,
    CONSOLE_COLOR_PURPLE, CONSOLE_COLOR_RESET,

    // The URL of StarkScript's GtiHub repository
    __STARK_GITHUB_URL__);

}
