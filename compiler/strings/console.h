/**
 *
 *  Manage all the console strings
 *
**/


// Define the console colours
// For more info about ANSI escape sequences, visit:
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
#define CONSOLE_COLOR_RESET "\e[0m"
#define CONSOLE_COLOR_BLACK "\e[0;30m"
#define CONSOLE_COLOR_RED "\e[0;31m"
#define CONSOLE_COLOR_GREEN "\e[0;32m"
#define CONSOLE_COLOR_YELLOW "\e[0;33m"
#define CONSOLE_COLOR_BLUE "\e[0;34m"
#define CONSOLE_COLOR_PURPLE "\e[0;35m"
#define CONSOLE_COLOR_CYAN "\e[0;36m"
#define CONSOLE_COLOR_WHITE "\e[0;37m"
#define CONSOLE_COLOR_GRAY "\e[38;5;240m"
#define CONSOLE_COLOR_DARK_GRAY "\e[38;5;236m"

// Define the prefix of debug console messages
#define STRING_CONSOLE_DEBUG_MESSAGE "[\e[0;36m*\e[0m][\e[0;36mDebug\e[0m] \e[38;5;240m->\e[0m "
#define STRING_CONSOLE_DEBUG_MESSAGE_NO_GRAY "[\e[0;36m*\e[0m][\e[0;36mDebug\e[0m] -> "
#define STRING_CONSOLE_DEBUG_MESSAGE_COLORLESS "[*][Debug] -> "
#define STRING_CONSOLE_CAT_DEBUG_MESSAGE "\e[38;5;153m  /ᐠ__ᐟ\\   \n=( \e[0;36mŌ\e[38;5;14m △ \e[0;36mŌ\e[38;5;153m)=\e[38;5;240m ∳ \e[0;36mDebug\e[0m\n             "
#define STRING_CONSOLE_CAT_DEBUG_MESSAGE_NO_GRAY "\e[38;5;153m  /ᐠ__ᐟ\\   \n=( \e[0;36mŌ\e[38;5;14m △ \e[0;36mŌ\e[38;5;153m)=\e[0m ∳ \e[0;36mDebug\e[0m\n             "
#define STRING_CONSOLE_CAT_DEBUG_MESSAGE_COLORLESS "  /ᐠ__ᐟ\\   \n=( Ō △ Ō)= ∳ Debug\n             "

// Define the prefix of informative console messages
#define STRING_CONSOLE_INFO_MESSAGE "[\e[0;32m?\e[0m][\e[0;32mInfo\e[0m] \e[38;5;240m->\e[0m "
#define STRING_CONSOLE_INFO_MESSAGE_NO_GRAY "[\e[0;32m?\e[0m][\e[0;32mInfo\e[0m] -> "
#define STRING_CONSOLE_INFO_MESSAGE_COLORLESS "[?][Info] -> "
#define STRING_CONSOLE_CAT_INFO_MESSAGE "\e[38;5;47m  /ᐠ__ᐟ\\   \n=( \e[0;32mÔ\e[38;5;48m △ \e[0;32mÔ\e[38;5;47m)=\e[38;5;240m ∳ \e[0;32mInfo\e[0m\n             "
#define STRING_CONSOLE_CAT_INFO_MESSAGE_NO_GRAY "\e[38;5;47m  /ᐠ__ᐟ\\   \n=( \e[0;32mÔ\e[38;5;48m △ \e[0;32mÔ\e[38;5;47m)=\e[0m ∳ \e[0;32mInfo\e[0m\n             "
#define STRING_CONSOLE_CAT_INFO_MESSAGE_COLORLESS "  /ᐠ__ᐟ\\   \n=( Ô △ Ô)= ∳ Info\n             "

// Define the prefix of warning console messages
#define STRING_CONSOLE_WARNING_MESSAGE "[\e[0;33m!\e[0m][\e[0;33mWarn\e[0m] \e[38;5;240m->\e[0m "
#define STRING_CONSOLE_WARNING_MESSAGE_NO_GRAY "[\e[0;33m!\e[0m][\e[0;33mWarn\e[0m] -> "
#define STRING_CONSOLE_WARNING_MESSAGE_COLORLESS "[!][Warn] -> "
#define STRING_CONSOLE_CAT_WARNING_MESSAGE "\e[38;5;222m  /ᐠ__ᐟ\\   \n=( \e[0;33mǑ\e[38;5;223m △ \e[0;33mǑ\e[38;5;222m)=\e[38;5;240m ∳ \e[0;33mWarn\e[0m\n             "
#define STRING_CONSOLE_CAT_WARNING_MESSAGE_NO_GRAY "\e[38;5;222m  /ᐠ__ᐟ\\   \n=( \e[0;33mǑ\e[38;5;223m △ \e[0;33mǑ\e[38;5;222m)=\e[0m ∳ \e[0;33mWarn\e[0m\n             "
#define STRING_CONSOLE_CAT_WARNING_MESSAGE_COLORLESS "  /ᐠ__ᐟ\\   \n=( Ǒ △ Ǒ)= ∳ Warn\n             "
#define STRING_CONSOLE_WARN_MESSAGE_LENGTH 13
#define STRING_CONSOLE_CAT_WARN_MESSAGE_LENGTH 13

// Define the prefix of error console messages
#define STRING_CONSOLE_ERROR_MESSAGE "[\e[0;31mx\e[0m][\e[0;31mError\e[0m] \e[38;5;240m->\e[0m "
#define STRING_CONSOLE_ERROR_MESSAGE_NO_GRAY "[\e[0;31mx\e[0m][\e[0;31mError\e[0m] -> "
#define STRING_CONSOLE_ERROR_MESSAGE_COLORLESS "[x][Error] -> "
#define STRING_CONSOLE_CAT_ERROR_MESSAGE "\e[38;5;210m  /ᐠ__ᐟ\\   \n=( \e[0;31mÒ\e[38;5;218m △ \e[0;31mÓ\e[38;5;210m)=\e[38;5;240m ∳ \e[0;31mError\e[0m\n             "
#define STRING_CONSOLE_CAT_ERROR_MESSAGE_NO_GRAY "\e[38;5;210m  /ᐠ__ᐟ\\   \n=( \e[0;31mÒ\e[38;5;218m △ \e[0;31mÓ\e[38;5;210m)=\e[0m ∳ \e[0;31mError\e[0m\n             "
#define STRING_CONSOLE_CAT_ERROR_MESSAGE_COLORLESS "  /ᐠ__ᐟ\\   \n=( Ò △ Ó)= ∳ Error\n             "
#define STRING_CONSOLE_ERROR_MESSAGE_LENGTH 14
#define STRING_CONSOLE_CAT_ERROR_MESSAGE_LENGTH 13

// Define the GitHub issue suggestion string
#define STRING_CONSOLE_GITHUB_REPORT "\e[0;36m\n\n            * Please, open an issue on our GitHub repository about this error! (visit https://github.com/EnderCommunity/StarkScript/issues/)\n\e[0m"
#define STRING_CONSOLE_GITHUB_REPORT_COLORLESS "\n\n            * Please, open an issue on our GitHub repository about this error! (visit https://github.com/EnderCommunity/StarkScript/issues/)\n"

// Define the colours that are going to be used for code blocks
#define CONSOLE_CODE_BLOCK "\e[48;5;238m\e[38;5;234m"
// #define CONSOLE_CODE_BLOCK_NO_GRAY "\e[48;5;15m\e[38;5;104m"
#define CONSOLE_CODE_BLOCK_LINE "\e[48;5;234m\e[38;5;238m"
//#define CONSOLE_CODE_BLOCK_LINE_NO_GRAY "\e[48;5;104m\e[38;5;15m"
#define CONSOLE_CODE_BLOCK_ERROR "\e[48;5;218m\e[38;5;124m"
#define CONSOLE_CODE_BLOCK_LINE_ERROR "\e[48;5;124m\e[38;5;218m"
#define CONSOLE_CODE_BLOCK_WARN "\e[48;5;224m\e[38;5;172m"
#define CONSOLE_CODE_BLOCK_LINE_WARN "\e[48;5;172m\e[38;5;224m"
