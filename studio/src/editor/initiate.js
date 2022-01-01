/**
 *
 * Manage the monaco editor
 *
 **/


// initiate the editor
require.config({

    paths: {

        vs: '../../../node_modules/monaco-editor/min/vs'

    }

});
require(['vs/editor/editor.main'], function() {

    console.log(monaco);

    // Start registering languages
    // window.langs = registerLanguages();

    /*var editor = monaco.editor.create(document.getElementById('container'), {

        value: ['function x() {', '\tconsole.log("Hello world!");', '}'].join('\n'),
        language: 'javascript'

    });*/

});