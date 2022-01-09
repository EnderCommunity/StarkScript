/**
 *
 * Manage languages and the registration process
 *
 **/


// Define a function that can register a language
function registerLang(name, tokenizer, theme, CIP) {

    // Register a new language
    monaco.languages.register({

        id: name,
        // extensions: ['.stark'],
        // aliases: ['Stark', 'stark', 'ss', 'SS', 'starkscript', 'StarkScript']

    });

    // Register a tokens provider for the language
    monaco.languages.setMonarchTokensProvider(name, tokenizer);

    // Define a new theme that contains only rules that match this language
    monaco.editor.defineTheme(name + "-theme-light", theme.light);
    monaco.editor.defineTheme(name + "-theme-dark", theme.dark);

    // Register a completion item provider for the new language
    monaco.languages.registerCompletionItemProvider(name, CIP);

    // Return the initialisation object of an editor set to view code for this language
    return {

        theme: name + "-theme-light",
        language: name

    };

}

// Define a function that will initialise this process
function registerLanguages() {

    // Define an object that can be used to keep track of the defined langauegs
    var langs = {};

    // Go through all the languages within the "languages" directory
    [

        "stark"

    ].forEach(function(lang) {

        // Get all the files from this language
        // import { lightTheme, darkTheme } from `./${lang}/theme.js`;
        // import { tokenizer } from `./${lang}/tokenizer.js`
        // import { CIP } from `./${lang}/CIP.js`;

        // Register the programming language
        langs[lang] = registerLang(lang, tokenizer, {

            light: lightTheme,
            dark: darkTheme

        }, CIP);

    });

    // Return the languages object
    return langs;

}