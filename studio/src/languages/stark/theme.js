// Source: https://microsoft.github.io/monaco-editor/playground.html#extending-language-services-custom-languages

0;

export var lightTheme = {

    base: 'vs',
    inherit: false,
    rules: [

        {
            token: 'string',
            foreground: 'A31515'
        }, {
            token: 'number',
            foreground: '09869E'
        }, {
            token: 'annotation',
            foreground: '795E26'
        }, {
            token: 'comment',
            foreground: '008000'
        }, {
            token: 'type',
            foreground: '267F99'
        }, {
            token: 'identifier',
            foreground: '0070CD'
        }, {
            token: 'keyword.type',
            foreground: '0000FF'
        }, {
            token: 'keyword.predefined',
            foreground: '0000FF'
        }, {
            token: 'compiler-constant',
            foreground: '001090'
        }, {
            token: 'keyword.definition',
            foreground: '0000FF'
        }, {
            token: 'keyword.functional',
            foreground: 'AF00DB'
        },

    ],
    colors: {


    }

};

export var darkTheme = {

    base: 'vs-dark',
    inherit: false,
    rules: [


        {
            token: 'operator',
            foreground: 'D4D4D4'
        }, {
            token: '',
            foreground: 'D4D4D4'
        }, {
            token: 'string',
            foreground: 'CE9178'
        }, {
            token: 'number',
            foreground: 'B5CEA8'
        }, {
            token: 'annotation',
            foreground: 'DCDCAA'
        }, {
            token: 'comment',
            foreground: '6A9955'
        }, {
            token: 'type',
            foreground: '4EC9B0'
        }, {
            token: 'identifier',
            foreground: '9CDCFE'
        }, {
            token: 'keyword.type',
            foreground: '569CD6'
        }, {
            token: 'keyword.predefined',
            foreground: '569CD6'
        }, {
            token: 'compiler-constant',
            foreground: '4FC1FF'
        }, {
            token: 'keyword.definition',
            foreground: '569CD6'
        }, {
            token: 'keyword.functional',
            foreground: 'C586C0'
        },

    ],
    colors: {


    }

};