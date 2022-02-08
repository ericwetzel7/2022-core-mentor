# Project Workflow
This section covers how the project will be managed, and how you can be organized so that nobody is working on the same code, and all code is combined safely.

## The Project Board
The main organization for this project will be managed through a project board on Github. To see the board:
1. Go to the "Projects" tab on Github.
2. Click on the "Projects" option on the left that has a "1" next to it.
3. Click on "2022 - Rapid React".

You should now see a board that has 4 columns: "To do", "In Progress", "In review", and "Done".
### To Do
This column contains all of the things yet to be done. 
### In Progress
This column contains all of the tasks currently being worked on.
### In Review 
This column contains all of the tasks that have been worked on, but haven't been approved yet.
### Done
This column is all previous tasks that have been completed. This column is purely for documentation.


# Git Workflow
This section covers how to manage the actual code, and the basic process required to manage it.

## Getting Started
Do these steps vefore you start working on a computer you haven't worked on before.

To do this:
1. Click the green "Code" dropdown at the top of this repository on Github. Make sure "HTTPS" is underlined, then click the clipboard icon to copy the URL it shows.
2. Go to the "Source Control" tab in Visual Studio Code (VS Code) (the brancing symbol on the far left). 
3. Click the button in the tab that shows up that says "Clone Repository", then paste in the URL you copied.
4. VS Code will prompt you to pick a destination for the download. Store it in "Documents\\FIRST\\2022" (or your operating system's equivalent).
5. When prompted, click "Open".

## Before you edit
When you have the code on your computer, and you haven't just cloned the project, make sure you do these steps.

1. Make sure you're in the proper branch (See: Branching) for what you're working on. You should never be working in `master`.
2. In VS Code's "Source Control" tab, click on the triple dot menu (...), navigate down to "Pull, Push", then click "Pull".
    - This makes sure you are upto-date with any other changes in the current branch.
3. Check again that you're in the proper branch for what you're working on. 
4. Triple check. Seriously, it will make life quite hard if you're in the wrong branch.
5. Edit away!

## Commiting Your Changes
This assumes you're already on the right branch. See "Branching" if you need to change branches.

When you have changes you're ready to save:
1. Open the "Source Control" tab in VS Code. You should see the files you've changed under "Changes".
    - If it's a new file, you'll see a "U" next to it (short for "Untracked").
    - Otherwise, it should have a "M" (short for "Modified").
2. Click the "+" sign next to the file's name. This should move it to a "Staged Changes" area. 
3. In the text box at the top (contains something like "Message..." by default), enter your commit message
    - This should be a short summary of the changes you made.
    - Start your message with a present tense verb (e.g. "Add function to class", instead of "Added function to class").
4. When you're ready, click the checkmark above the text area to commit your changes.
5. You don't have to click the "Sync Changes" button at this point, but you can. For more information, see "Syncing with Github".

### Syncing with Github
This only works when you have commits on your computer that you haven't already pushed. This will not push uncommited changes.

1. In the "Source Control" tab in VS Code, if you have unsynced commits, you should be able to click the "Sync Changes" button, and you're done.
    - This both pulls from Github, then pushes your commit(s).
    - If you have something called a "merge conflict", talk to a programming mentor (probably Kellen), and they'll help you resolve it. 
2. If you don't see that button, you can click on the triple dot menu (...), navigate down to "Pull, Push", then click "Sync". 
This has the same effect as above. The same advice applies to merge conflicts here.


## Branching
These rules define how to name and use branches with Git.

If you are working on a subsytem, you should be in one of the existing `subsystem/\<subsystem\_name>` branches. You will never create one of these. 
If you think you need to work on a branch that doesn't already exist, tell a programming mentor (probably Kellen), and they'll deal with it.

Command branches should all be named `command/\<command\_name>`. If a branch exists for what you're working on, check that branch out. Otherwise, create a 
branch named with that pattern, and check it out.

You should never touch any branch named `master` or `deploy`. These are purely for admins, and you may break something important if you mess with them 
(or at least make someone's life harder than necessary).

### Creating a New Branch
1. In VS Code, in the "Source Control" menu, click on the triple dot menu (...), navigate down to "Checkout to...".
2. click the "+ Create New Branch" option, then enter the name of your branch (probably `command/\<something>`).
3. Click the "Publish Branch" option that appears in the "Source Control" tab. This syncs it with Github.
4. You're now in that branch, so edit to your heart's content.

### Checking Out an Existing Branch
1. In VS Code, in the "Source Control" menu, click on the triple dot menu (...), navigate down to "Checkout to...".
2. Click the branch you want to edit. Don't check out branches that start with `origin`

If you don't see the branch you want to edit, it doesn't exist. If you thought it did, talk to the programming mentor (probably Kellen), 
and they'll help you sort it out. Otherwise, create it using the instructions in "Creating a New Branch".

