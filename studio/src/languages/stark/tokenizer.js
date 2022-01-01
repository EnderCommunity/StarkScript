// https://microsoft.github.io/monaco-editor/monarch.html

// Create your own language definition here
// You can safely look at other samples without losing modifications.
// Modifications are not saved on browser refresh/close though -- copy often!
export var tokenizer = {

    // Set defaultToken to invalid to see what you do not tokenize yet
    // defaultToken: 'invalid',

    definingKeywords: [

        "function", "variable", "constant", "condition", "class"

    ],
    functionalKeywords: [

        "use", "import", "start", "append", "new", "define", "delete", "constructor"

    ],
    typeKeywords: [

        "bool", "double", "int", "short", "char", "void", "long", "float", "string"

    ],
    predefinedKeywords: [

        "this"

    ],

    // Remember to add all these operators to the language!
    operators: [

        "=", ">", "<", "!", "~", "?", ":", "==", "<=", ">=", "!=", "&&", "||", "++", "--", "+", "-",
        "*", "/", "&", "|", "^", "%", "<<", ">>", ">>>", "+=", "-=", "*=", "/=", "&=", "|=", "^=",
        "%=", "<<=", ">>=", ">>>="

    ],

    // we include these common regular expressions
    symbols: /[=><!~?:&|+\-*\/\^%]+/,

    // C# style strings
    escapes: /\\(?:[abfnrtv\\"']|x[0-9A-Fa-f]{1,4}|u[0-9A-Fa-f]{4}|U[0-9A-Fa-f]{8})/,

    // The main tokenizer for our languages
    tokenizer: {

        root: [

            // identifiers and keywords
            [

                /[a-z_$][\w$]*/,
                {

                    cases: {

                        "@typeKeywords": "keyword.type",
                        "@functionalKeywords": "keyword",
                        "@definingKeywords": "keyword",
                        "@predefinedKeywords": "keyword",
                        "@default": "identifier",

                    },

                },

            ],

            [

                /[A-Z][\w\$]*/, "type.identifier" // to show class names nicely

            ],

            // whitespace
            {

                include: "@whitespace"

            },

            // delimiters and operators
            [

                /[{}()\[\]]/, "@brackets"

            ],
            [

                /[<>](?!@symbols)/, "@brackets"

            ],
            [

                /@symbols/,
                {

                    cases: {

                        "@operators": "operator",
                        "@default": "",

                    },

                },

            ],

            // @ annotations.
            [

                /@[\w:]*/,
                {

                    token: "annotation",
                    log: "annotation token: $0"

                }

            ],

            // numbers
            [

                /\d*\.\d+([eE][\-+]?\d+)?/, "number.hex"

            ],
            [

                /0[xX][0-9a-fA-F]+/, "number.hex"

            ],
            [

                /\d+/, "number.hex"

            ],

            // delimiter: after number because of .\d floats
            [

                /[;,.]/, "delimiter"

            ],

            // strings
            [

                /"([^"\\]|\\.)*$/, "string.invalid"

            ], // non-teminated string
            [

                /"/,
                {

                    token: "string.quote",
                    bracket: "@open",
                    next: "@string"

                }

            ],

            // characters
            [

                /'[^\\']'/, "string"

            ],
            [

                /(')(@escapes)(')/, ["string", "string.escape", "string"]

            ],
            [

                /'/, "string.invalid"

            ],

        ],

        comment: [

            [

                /[^\/*]+/, "comment"

            ],
            [

                /\/\*/, "comment", "@push"

            ], // nested comment
            [

                "\\*/", "comment", "@pop"

            ],
            [

                /[\/*]/, "comment"

            ],

        ],

        string: [

            [

                /[^\\"]+/, "string"

            ],
            [

                /@escapes/, "string.escape"

            ],
            [

                /\\./, "string.escape.invalid"

            ],
            [

                /"/,
                {

                    token: "string.quote",
                    bracket: "@close",
                    next: "@pop"

                }

            ],

        ],

        whitespace: [

            [

                /[ \t\r\n]+/, "white"

            ],
            [

                /\/\*/, "comment", "@comment"

            ],
            [

                /\/\/.*$/, "comment"

            ],

        ],

    },

};