/**
 * \page gameobject-hierarchy The GameObject Hierarchy
 * 
 * Games built using the Gluon game engine, GluonEngine, are called GameProjects. They consist of a
 * variety of different types of objects, which work together to create a game. The following is a
 * short introduction to how the structure of a GameProject works. You can start working with Gluon
 * Creator without this knowledge, but it will make your life easier if you understand these basic
 * terms, as they are used throughout the rest of the documentation.
 *
 * \section goh-the-gameobject-hierarchy The GameObject Hierarchy
 * 
 * At the top of the Gluon GameObject Hierarchy is the GameProject, which is basically your entire
 * game. A GameProject contains one or more Scenes, which can be anything from a level map or a menu
 * screen. A Scene is composed of one or more GameObjects. A GameObject is a tree of GameObjects or
 * any number of Components. A GameObject represents a functional unit in a scene, like a Car
 * object, which can also be made up of other parts which are GameObjects in themselves (like a
 * rocket backpack or a weapon). Components provide the logic that operates on the GameObject they
 * are attached to. Components can be attached to any number of Assets. Assets simply represent a
 * piece of data stored on disk, like a sound file or an image file. 
 * 
 * The GameObject hierachy is made up of instances of GluonEngine::GameObject in a tree structure
 * with a parent-child system, each with any number of GluonEngine::Component instances. The
 * Components provide most of the logic in the game, and since so many are usable in so many places,
 * Gluon would ship with a number of pre-created Components (such as a Camera, Input handlers,
 * MeshRenderer, TextureRenderer and so on). 
 * 
 * The logic behind creating this system is to enable the game programmer to enforce encapsulation
 * and create reusable components, which can then be applied to numerous GameObjects. It also allows
 * for sane separation of the different types of logic required for each part of a GameObject, thus
 * potentially creating cleaner, more readable code. At the same time, the structure described here
 * would allow for the creation of a graphical tool to manage all of the components' settings.
 * Components are implemented as plugins, making the code even more flexible and separated. 
 *
 * \section goh-components More on Components
 * 
 * Components are like properties that you can attach to GameObjects, such as a "render" Component
 * that actually makes the GameObject visible, or a "SoundListener" Component that gives the object
 * the ability to listen to sounds. Components can also be scripts that controls the behaviour of
 * the GameObjects attached to them. All GameObjects in Gluon have their Transform properties
 * built-in, giving the object its position, rotation, and scale (it doesn't make much sense to have
 * an object that doesn't have at least a position). Components do not have Transform properties,
 * but the GameObject to which a Component is attached to does.
 */