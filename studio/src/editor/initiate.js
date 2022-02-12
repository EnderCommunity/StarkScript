/**
 *
 * Manage the monaco editor
 *
 **/


// initiate the editor
const editors = {
    settings: null
};
require.config({

    paths: {

        vs: '../../../node_modules/monaco-editor/min/vs'

    }

});
require(['vs/editor/editor.main'], function() {

    console.log(monaco);

    // Get the needed settings data
    electron.getData({

        editorSettings: true

    }, function(data) {

        console.log(data.editorSettings);

        // Store this value
        editors.settings = data.editorSettings;

        // Start loading the session
        loadSession();

    });

    // Start registering languages
    // window.langs = registerLanguages();

    /*var editor = monaco.editor.create(document.getElementById('container'), {

        value: ['function x() {', '\tconsole.log("Hello world!");', '}'].join('\n'),
        language: 'javascript'

    });*/

});