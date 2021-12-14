/**
 *
 *  Manage all the console strings
 *
**/


// Define the console colours
// For more info about ANSI escape sequences, visit:
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
#define CONSOLE_COLOR_RESET "\033[0m"
#define CONSOLE_COLOR_BLACK "\033[0;30m"
#define CONSOLE_COLOR_RED "\033[0;31m"
#define CONSOLE_COLOR_GREEN "\033[0;32m"
#define CONSOLE_COLOR_YELLOW "\033[0;33m"
#define CONSOLE_COLOR_BLUE "\033[0;34m"
#define CONSOLE_COLOR_PURPLE "\033[0;35m"
#define CONSOLE_COLOR_CYAN "\033[0;36m"
#define CONSOLE_COLOR_WHITE "\033[0;37m"
#define CONSOLE_COLOR_GRAY "\033[38;5;240m"
#define CONSOLE_COLOR_DARK_GRAY "\033[38;5;236m"

// Define the prefix of debug console messages
#define STRING_CONSOLE_DEBUG_MESSAGE "[\033[0;36m*\033[0m][\033[0;36mDebug\033[0m] \033[38;5;240m->\033[0m "
#define STRING_CONSOLE_DEBUG_MESSAGE_NO_GRAY "[\033[0;36m*\033[0m][\033[0;36mDebug\033[0m] -> "
#define STRING_CONSOLE_DEBUG_MESSAGE_COLORLESS "[*][Debug] -> "
#define STRING_CONSOLE_CAT_DEBUG_MESSAGE "\033[38;5;153m  /ᐠ__ᐟ\\   \n=( \033[0;36mŌ\033[38;5;14m △ \033[0;36mŌ\033[38;5;153m)=\033[38;5;240m ∳ \033[0;36mDebug\033[0m\n             "
#define STRING_CONSOLE_CAT_DEBUG_MESSAGE_NO_GRAY "\033[38;5;153m  /ᐠ__ᐟ\\   \n=( \033[0;36mŌ\033[38;5;14m △ \033[0;36mŌ\033[38;5;153m)=\033[0m ∳ \033[0;36mDebug\033[0m\n             "
#define STRING_CONSOLE_CAT_DEBUG_MESSAGE_COLORLESS "  /ᐠ__ᐟ\\   \n=( Ō △ Ō)= ∳ Debug\n             "

// Define the prefix of informative console messages
#define STRING_CONSOLE_INFO_MESSAGE "[\033[0;32m?\033[0m][\033[0;32mInfo\033[0m] \033[38;5;240m->\033[0m "
#define STRING_CONSOLE_INFO_MESSAGE_NO_GRAY "[\033[0;32m?\033[0m][\033[0;32mInfo\033[0m] -> "
#define STRING_CONSOLE_INFO_MESSAGE_COLORLESS "[?][Info] -> "
#define STRING_CONSOLE_CAT_INFO_MESSAGE "\033[38;5;47m  /ᐠ__ᐟ\\   \n=( \033[0;32mÔ\033[38;5;48m △ \033[0;32mÔ\033[38;5;47m)=\033[38;5;240m ∳ \033[0;32mInfo\033[0m\n             "
#define STRING_CONSOLE_CAT_INFO_MESSAGE_NO_GRAY "\033[38;5;47m  /ᐠ__ᐟ\\   \n=( \033[0;32mÔ\033[38;5;48m △ \033[0;32mÔ\033[38;5;47m)=\033[0m ∳ \033[0;32mInfo\033[0m\n             "
#define STRING_CONSOLE_CAT_INFO_MESSAGE_COLORLESS "  /ᐠ__ᐟ\\   \n=( Ô △ Ô)= ∳ Info\n             "

// Define the prefix of warning console messages
#define STRING_CONSOLE_WARNING_MESSAGE "[\033[0;33m!\033[0m][\033[0;33mWarn\033[0m] \033[38;5;240m->\033[0m "
#define STRING_CONSOLE_WARNING_MESSAGE_NO_GRAY "[\033[0;33m!\033[0m][\033[0;33mWarn\033[0m] -> "
#define STRING_CONSOLE_WARNING_MESSAGE_COLORLESS "[!][Warn] -> "
#define STRING_CONSOLE_CAT_WARNING_MESSAGE "\033[38;5;222m  /ᐠ__ᐟ\\   \n=( \033[0;33mǑ\033[38;5;223m △ \033[0;33mǑ\033[38;5;222m)=\033[38;5;240m ∳ \033[0;33mWarn\033[0m\n             "
#define STRING_CONSOLE_CAT_WARNING_MESSAGE_NO_GRAY "\033[38;5;222m  /ᐠ__ᐟ\\   \n=( \033[0;33mǑ\033[38;5;223m △ \033[0;33mǑ\033[38;5;222m)=\033[0m ∳ \033[0;33mWarn\033[0m\n             "
#define STRING_CONSOLE_CAT_WARNING_MESSAGE_COLORLESS "  /ᐠ__ᐟ\\   \n=( Ǒ △ Ǒ)= ∳ Warn\n             "

// Define the prefix of error console messages
#define STRING_CONSOLE_ERROR_MESSAGE "[\033[0;31mx\033[0m][\033[0;31mError\033[0m] \033[38;5;240m->\033[0m "
#define STRING_CONSOLE_ERROR_MESSAGE_NO_GRAY "[\033[0;31mx\033[0m][\033[0;31mError\033[0m] -> "
#define STRING_CONSOLE_ERROR_MESSAGE_COLORLESS "[x][Error] -> "
#define STRING_CONSOLE_CAT_ERROR_MESSAGE "\033[38;5;210m  /ᐠ__ᐟ\\   \n=( \033[0;31mÒ\033[38;5;218m △ \033[0;31mÓ\033[38;5;210m)=\033[38;5;240m ∳ \033[0;31mError\033[0m\n             "
#define STRING_CONSOLE_CAT_ERROR_MESSAGE_NO_GRAY "\033[38;5;210m  /ᐠ__ᐟ\\   \n=( \033[0;31mÒ\033[38;5;218m △ \033[0;31mÓ\033[38;5;210m)=\033[0m ∳ \033[0;31mError\033[0m\n             "
#define STRING_CONSOLE_CAT_ERROR_MESSAGE_COLORLESS "  /ᐠ__ᐟ\\   \n=( Ò △ Ó)= ∳ Error\n             "

// Define the GitHub issue suggestion string
#define STRING_CONSOLE_GITHUB_REPORT "\033[0;36m\n\n            * Please, open an issue on our GitHub repository about this error! (visit https://github.com/EnderCommunity/StarkScript/issues/)\n\033[0m"
#define STRING_CONSOLE_GITHUB_REPORT_COLORLESS "\n\n            * Please, open an issue on our GitHub repository about this error! (visit https://github.com/EnderCommunity/StarkScript/issues/)\n"
