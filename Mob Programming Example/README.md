# Proxy Refactoring Example

Hello and congratulations on accepting an offer with MicroSlop! You have been assigned to work on the MicroSlop SuperOffice (TM) suite of productivity tools!

Recently we have recieved a number of complaints from users stating that their documents are very slow to load. Specifically our complaints are coming from our users who have a large number of equations or images in their documents. Despite our intern's best efforts they could not optimize the loading of images or rendering of equations. This has convinced us at MicroSlop that our equation renderer and image loader are still the best in the industry, and therefore cannot be improved upon.

Despite how many times we tell the users this, they still complain about how slow documents load, how ungrateful! Can you take a look to see if you can make documents load faster even though our state-of-the-art image and equation renders can't be improved? Ted from DoorsOS team suggests using a "Proxy" class, but what does he know, he's an OS dev. He claims that you can use the proxy to delay loading the image or equation until its visible on screen. He also claims you can use the proxy to cache the image so that it loads instantly on the next render.

We aren't quite sure if we can believe Ted. Can you investigate this?


## Your Task:

Refactor the provided code to use the proxy design pattern to get documents to load faster and get our customers to stop complaining.
You should keep the `MicroSlopSuperOffice::DocumentComponent` interface the same as it is, your teammate Susan is working on a new component and will be very upset with you if you change the interface. 

