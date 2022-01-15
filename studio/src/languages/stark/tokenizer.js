// https://microsoft.github.io/monaco-editor/monarch.html

// Create your own language definition here
// You can safely look at other samples without losing modifications.
// Modifications are not saved on browser refresh/close though -- copy often!
export var tokenizer = {

    // Set defaultToken to invalid to see what you do not tokenize yet
    // defaultToken: 'invalid',
    keyword: [

        "use", "import"

    ],
    keywordNR: [

        "execute", "append", "obscure", "new", "define", "delete", "if", "else", "return", "exit",
        "intermediate", "constructor", "destructor", "extend", "await", "get", "from"

    ],

    definitionalKeyword: [

        // ...

    ],
    definitionalKeywordNR: [

        "function", "variable", "constant", "condition", "class"

    ],

    typeKeyword: [

        // ...

    ],
    typeKeywordNR: [

        "bool", "double", "int", "short", "char", "void", "long", "float", "string"

    ],

    referenceKeyword: [

        // ...

    ],
    referenceKeywordNR: [

        "this", "super"

    ],

    boolean: [

        // ...

    ],
    booleanNR: [

        "true", "false"

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

            [/%%(.*?)%%/, "compiler-constant"],
            [/'(.*?)'/, "string"],

            // identifiers and keywords
            [

                /[a-z_$][\w$]*/, {

                    cases: {

                        "@keyword": "keyword.functional",
                        "@definitionalKeyword": "keyword.definition",
                        "@typeKeyword": "keyword.type",
                        "@referenceKeyword": "keyword.predefined",
                        "@boolean": "keyword.predefined",

                        "@keywordNR": "invalid",
                        "@definitionalKeywordNR": "invalid",
                        "@typeKeywordNR": "invalid",
                        "@referenceKeywordNR": "invalid",
                        "@booleanNR": "invalid",

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

                /@symbols/, {

                    cases: {

                        "@operators": "operator",
                        "@default": "",

                    },

                },

            ],

            // @ annotations.
            [

                /@[a-zA-Z][a-zA-Z_0-9]*/, {

                    token: "invalid" // Change to "annotation" when you implement this!

                }

            ],
            // numbers
            [

                /\d*\.\d+([eE][\-+]?\d+)?/, "invalid" // Change this to "number.hex"

            ],
            [

                /0[xX][0-9a-fA-F]+/, "invalid" // Change this to "number.hex"

            ],
            [

                /\d+/, "invalid" // Change this to "number.hex"

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

                /"/, {

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

                /"/, {

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