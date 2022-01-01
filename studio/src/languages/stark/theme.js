// Source: https://microsoft.github.io/monaco-editor/playground.html#extending-language-services-custom-languages

export var lightTheme = {

    base: 'vs',
    inherit: false,
    rules: [

        { token: 'custom-info', foreground: '808080' },
        { token: 'custom-error', foreground: 'ff0000', fontStyle: 'bold' },
        { token: 'custom-notice', foreground: 'FFA500' },
        { token: 'custom-date', foreground: '008800' }

    ],
    colors: {

        'editor.foreground': '#000000'

    }

};

export var darkTheme = {

    base: 'vs',
    inherit: false,
    rules: [

        { token: 'custom-info', foreground: '808080' },
        { token: 'custom-error', foreground: 'ff0000', fontStyle: 'bold' },
        { token: 'custom-notice', foreground: 'FFA500' },
        { token: 'custom-date', foreground: '008800' }

    ],
    colors: {

        'editor.foreground': '#000000'

    }

};