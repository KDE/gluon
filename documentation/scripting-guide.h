/**
 * \page scripting-guide Scripting Guide
 * 
 * This part of the documentation describes how to use the scripting system in GluonEngine to build
 * your own game logic - best practices and introduction guides are shown along with code samples
 * that you can use directly in your games.
 * 
 * \note All samples shown in the documentation are provided under the Creative Commons Attribution
 * 3.0 Unported License ( http://creativecommons.org/licenses/by/3.0/ ) and you should ensure that
 * this license is sufficient to your game.
 * 
 * \section scripting-introduction Introducion to Scripting
 * 
 * When you hit the limit of the capabilities of the many Components provided by GluonEngine, it is
 * time to create your own game logic. This is where the QtScript Component comes in. Using this
 * component, you can use ECMA-Script (better known as JavaScript) to react to changes in the game
 * world, and make changes to the world in return. The scripts are written in version 1.5 of the
 * language, using the powerful QtScript engine, which is based on JavaScriptCore. If you are
 * familiar with JavaScript from web developing you are in good shape, but its important to note
 * that web browser specific extensions like DOM and some functions are not available.
 * 
 * \subsection scripting-resources Resources
 * 
 * The following is an introduction to how these scripts are written, and how they access the
 * various parts of the game. If you are looking for the full scripting API, please look at the
 * following links which are helpfully collected by the Amarok team, who use the same scripting
 * engine:
 * 
 * - <b><a href="http://developer.mozilla.org/en/docs/Core_JavaScript_1.5_Guide">JavaScript 1.5
 *   Guide</a></b>
 *      - A thorough overview of the language.
 * - <b><a href="http://developer.mozilla.org/en/docs/Core_JavaScript_1.5_Reference">API
 *   documentation for the standard functions and objects</a></b>
 *      - This documents some functions only available in JavaScript 1.6, which QtScript does not
 *        support; they are marked as such.
 * - <b><a href="http://doc.trolltech.com/4.4/ecmascript.html">Quick reference</a></b>
 *      - A Trolltech provided list of objects and functions.
 *
 * There are also many other JavaScript guides and tutorials on the Internet. Though often
 * web-browser oriented, many are still relevant.
 * 
 * \section scripting-api Introduction to the API
 * 
 * Before you start working with building scripts for game logic, you should know how
 * \ref gameobject-hierarchy works. The reason for this is that when constructing game logic you
 * will be interacting heavily with that hierarchy. The following image shows how it all fits
 * together:
 * 
 * \TODO image showing the hierarchy, and a "you are here" marker to show where the script object
 * sits
 * 
 * To enable you to interact in a simple manner with the other parts of the game, the most immediate
 * of each of the four classes of objects in the hierarchy, you have available to you the following
 * five special objects:
 * 
 * - <b>this.Game</b> The game engine itself, as represented by the GluonEngine::Game class
 * - <b>this.GameProject</b> The GameProject which represents the current game
 * - <b>this.Scene</b> The scene which this script's GameObject is tied to
 * - <b>this.GameObject</b> The GameObject this script's ScriptingComponent is tied to
 * - <b>this.Component</b> The ScriptingComponent this script is tied to
 * 
 * - special objects
 * - how to access objects by name, index...
 * - automagic (properties, exposed in Creator...)
 * - calling functions on other script objects
 * - some best practices about where to store data for your games...
 * 
 */