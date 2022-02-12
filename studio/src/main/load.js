/**
 * 
 * Load the main window
 * 
 **/


// Get the projects container
var projectsElm = document.getElementById("projects");

// Update the window's status
setTimeout(function() {

    electron.send("main-window-ready");

}, 1500);

// Get the path of the current root folder
electron.filesSystem.path.getAbsolute("./", function(path) {

    console.log(path);
    loadProjects(path);

});

// Load up the projects
var projectsList;

function loadProjects(rootPath) {

    projectsList = [];

    electron.filesSystem.readDir("./data/projects/", function(result) {

        var count = 0,
            finishList = function() {

                if (count == result.folders.length) {

                    if (projectsList.length == 0) {

                        projectsElm.setAttribute("message", $$("basic-interface:main.projects.empty"));

                    } else {

                        updateProjectsElm();
                        projectsElm.removeAttribute("message");

                    }

                }

            };

        result.folders.forEach(function(folder) {

            electron.filesSystem.readFile(`./data/projects/${folder}/manifest.json`, function(didFail, data) {

                if (!didFail) {

                    data = JSON.parse(data);

                    // Check the integrity of the manifest
                    // ...

                    projectsList.push({

                        name: data.name,
                        dir: `${rootPath}/data/projects/${folder}/`

                    })

                }

                count++;
                finishList();

            });

        });

    });

}

// Update the projects element
function updateProjectsElm() {

    projectsElm.innerHTML = "";

    projectsList.forEach(function(project) {

        projectsElm.innerHTML +=
            `<div class="projects--item projects--project" clickable>
                <img class="item--icon">
                <div class="item--info">
                    <text class="item--name">${project.name}</text>
                    <text class="item--extra">${project.dir}</text>
                </div>
            </div>`;

    });

}

// Show an alert window!!!!
// electron.alert("Test", electron.alertType.info, "This is a test", function() {
// 
//     console.log(1);
// 
// });