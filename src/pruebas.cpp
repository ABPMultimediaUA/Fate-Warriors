/*
 * pruebas.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: manu
 */

#include "Engine.h"
#include "EventManager.h"
#include "irrlicht.h"

enum {
	// I use this ISceneNode ID to indicate a scene node that is
	// not pickable by getSceneNodeAndCollisionPointFromRay()
	ID_IsNotPickable = 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be picked by ray selection.
	IDFlag_IsPickable = 1 << 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be highlighted. In this example, the
	// homonids can be highlighted, but the level mesh can't.
	IDFlag_IsHighlightable = 1 << 1
};



void pruebaCol1() {

	EventManager receiver;
	// ask user for driver
	//video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	//if (driverType==video::EDT_OPENGL)
	//   return 1;

	// create device

	IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
			core::dimension2d<u32>(640, 480), 16, false, false, false,
			&receiver);



	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	device->getFileSystem()->addFileArchive(
			"../FateWarriors/media/map-20kdm2.pk3");

	scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
	scene::IMeshSceneNode* q3node = 0;

	// The Quake mesh is pickable, but doesn't get highlighted.
	if (q3levelmesh)
		q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0), 0,
				IDFlag_IsPickable);

	scene::ITriangleSelector* selector = 0;

	if (q3node) {
		q3node->setPosition(core::vector3df(-1350, -130, -1400));

		selector = smgr->createOctreeTriangleSelector(q3node->getMesh(), q3node,
				128);

		q3node->setTriangleSelector(selector);
		q3node->setDebugDataVisible(true);

		// We're not done with this selector yet, so don't drop it.
	}

	// Set a jump speed of 3 units per second, which gives a fairly realistic jump
	// when used with the gravity of (0, -10, 0) in the collision response animator.
	scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f,
			.3f, ID_IsNotPickable, 0, 0, true, 3.f);
	camera->setPosition(core::vector3df(50, 50, -60));
	camera->setTarget(core::vector3df(-70, 30, -60));

	//*** CREACION DEL PERSONAJE ***///
	device->getFileSystem()->addFileArchive(
			"../FateWarriors/models/assassins-creed-altair-obj.zip");
	scene::IAnimatedMesh* meshAltair = smgr->getMesh(
			"assassins-creed-altair.obj");
	scene::ISceneNode* node5;
	if (meshAltair) {
		node5 = smgr->addOctTreeSceneNode(meshAltair->getMesh(0), 0, -1, 1024);
		//node = smgr->addSphereSceneNode();
	}

	const core::aabbox3d<f32>& box = node5->getBoundingBox();
	core::vector3df radius = box.MaxEdge - box.getCenter();

	node5->setPosition(core::vector3df(100, -50, 0));

	//node->setMaterialTexture(0, driver->getTexture("../../media/wall.bmp"));
	node5->setMaterialFlag(video::EMF_LIGHTING, false);
	node5->setTriangleSelector(selector);

	if (selector) {
		scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
				selector, node5, radius, core::vector3df(0, -10, 0),
				core::vector3df(0, 30, 0));
		selector->drop(); // As soon as we're done with the selector, drop it.
		node5->addAnimator(anim);

		anim->drop(); // And likewise, drop the animator when we're done referring to it.
		node5->setDebugDataVisible(true);
	}

	// Now I create three animated characters which we can pick, a dynamic light for
	// lighting them, and a billboard for drawing where we found an intersection.

	// First, let's get rid of the mouse cursor.  We'll use a billboard to show
	// what we're looking at.
	device->getCursorControl()->setVisible(false);

	// Add the billboard.
	scene::IBillboardSceneNode * bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	bill->setMaterialTexture(0,
			driver->getTexture(
					"../FateWarriors/media/particle.bmp"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
	bill->setID(ID_IsNotPickable); // This ensures that we don't accidentally ray-pick it

	scene::IAnimatedMeshSceneNode* node = 0;

	video::SMaterial material;

	// Add an MD2 node, which uses vertex-based animation.
	node =
			smgr->addAnimatedMeshSceneNode(
					smgr->getMesh(
							"../FateWarriors/media/faerie.md2"),
					0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	node->setPosition(core::vector3df(-90, -15, -140)); // Put its feet on the floor.
	node->setScale(core::vector3df(1.6f)); // Make it appear realistically scaled
	node->setMD2Animation(scene::EMAT_POINT);
	node->setAnimationSpeed(20.f);
	material.setTexture(0, driver->getTexture("../../media/faerie2.bmp"));
	material.Lighting = true;
	material.NormalizeNormals = true;
	node->getMaterial(0) = material;

	// Now create a triangle selector for it.  The selector will know that it
	// is associated with an animated node, and will update itself as necessary.
	selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop(); // We're done with this selector, so drop it now.

	// And this B3D file uses skinned skeletal animation.
	node =
			smgr->addAnimatedMeshSceneNode(
					smgr->getMesh(
							"../FateWarriors/media/ninja.b3d"),
					0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	node->setScale(core::vector3df(10));
	node->setPosition(core::vector3df(-75, -66, -80));
	node->setRotation(core::vector3df(0, 90, 0));
	node->setAnimationSpeed(8.f);
	node->getMaterial(0).NormalizeNormals = true;
	node->getMaterial(0).Lighting = true;
	// Just do the same as we did above.
	selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop();

	// This X files uses skeletal animation, but without skinning.
	node =
			smgr->addAnimatedMeshSceneNode(
					smgr->getMesh(
							"../FateWarriors/media/dwarf.x"),
					0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	node->setPosition(core::vector3df(-70, -66, -30)); // Put its feet on the floor.
	node->setRotation(core::vector3df(0, -90, 0)); // And turn it towards the camera.
	node->setAnimationSpeed(20.f);
	node->getMaterial(0).Lighting = true;
	selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop();

	// And this mdl file uses skinned skeletal animation.
	node =
			smgr->addAnimatedMeshSceneNode(
					smgr->getMesh(
							"../FateWarriors/media/yodan.mdl"),
					0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	node->setPosition(core::vector3df(-90, -25, 20));
	node->setScale(core::vector3df(0.8f));
	node->getMaterial(0).Lighting = true;
	node->setAnimationSpeed(20.f);

	// Just do the same as we did above.
	selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop();

	material.setTexture(0, 0);
	material.Lighting = false;

	// Add a light, so that the unselected nodes aren't completely dark.
	scene::ILightSceneNode * light = smgr->addLightSceneNode(0,
			core::vector3df(-60, 100, 400),
			video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 600.0f);
	light->setID(ID_IsNotPickable); // Make it an invalid target for selection.

	// Remember which scene node is highlighted
	scene::ISceneNode* highlightedSceneNode = 0;
	scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	int lastFPS = -1;

	// draw the selection triangle only as wireframe
	material.Wireframe = true;
	core::vector3df nodePosition = node5->getPosition();
	u32 then = device->getTimer()->getTime();
	core::vector3df nodeRotation;
	// This is the movemen speed in units per second.
	const f32 MOVEMENT_SPEED = 200.f;
	while (device->run()) {
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32) (now - then) / 1000.f; // Time in seconds
		then = now;
		if (receiver.IsKeyDown(irr::KEY_KEY_W)) {
			nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
			//nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime * (float)sin(360.0f - direction);
			//nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime * (float)cos(360.0f - direction);
			nodeRotation = core::vector3df(0, 0, 0);

		}

		else if (receiver.IsKeyDown(irr::KEY_KEY_S)) {
			nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
			nodeRotation = core::vector3df(0, 180, 0);
		}

		if (receiver.IsKeyDown(irr::KEY_KEY_A)) {
			nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
			nodeRotation = core::vector3df(0, -90, 0);
		}

		else if (receiver.IsKeyDown(irr::KEY_KEY_D)) {
			nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
			nodeRotation = core::vector3df(0, 90, 0);
		}

		node5->setPosition(nodePosition);
		node5->setRotation(nodeRotation);
		if (device->isWindowActive()) {

			driver->beginScene(true, true, 0);
			smgr->drawAll();

			// Unlight any currently highlighted scene node
			if (highlightedSceneNode) {
				highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING,
						true);
				highlightedSceneNode = 0;
			}

			// All intersections in this example are done with a ray cast out from the camera to
			// a distance of 1000.  You can easily modify this to check (e.g.) a bullet
			// trajectory or a sword's position, or create a ray from a mouse click position using
			// ISceneCollisionManager::getRayFromScreenCoordinates()
			core::line3d<f32> ray;
			ray.start = camera->getPosition();
			ray.end = ray.start
					+ (camera->getTarget() - ray.start).normalize() * 1000.0f;

			// Tracks the current intersection point with the level or a mesh
			core::vector3df intersection;
			// Used to show with triangle has been hit
			core::triangle3df hitTriangle;

			// This call is all you need to perform ray/triangle collision on every scene node
			// that has a triangle selector, including the Quake level mesh.  It finds the nearest
			// collision point/triangle, and returns the scene node containing that point.
			// Irrlicht provides other types of selection, including ray/triangle selector,
			// ray/box and ellipse/triangle selector, plus associated helpers.
			// See the methods of ISceneCollisionManager
			scene::ISceneNode * selectedSceneNode =
					collMan->getSceneNodeAndCollisionPointFromRay(ray,
							intersection, // This will be the position of the collision
							hitTriangle, // This will be the triangle hit in the collision
							IDFlag_IsPickable, // This ensures that only nodes that we have
							// set up to be pickable are considered
							0);// Check the entire scene (this is actually the implicit default)

			// If the ray hit anything, move the billboard to the collision position
			// and draw the triangle that was hit.
			if (selectedSceneNode) {
				bill->setPosition(intersection);

				// We need to reset the transform before doing our own rendering.
				driver->setTransform(video::ETS_WORLD, core::matrix4());
				driver->setMaterial(material);
				driver->draw3DTriangle(hitTriangle,
						video::SColor(0, 255, 0, 0));

				// We can check the flags for the scene node that was hit to see if it should be
				// highlighted. The animated nodes can be highlighted, but not the Quake level mesh
				if ((selectedSceneNode->getID() & IDFlag_IsHighlightable)
						== IDFlag_IsHighlightable) {
					highlightedSceneNode = selectedSceneNode;

					// Highlighting in this case means turning lighting OFF for this node,
					// which means that it will be drawn with full brightness.
					highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING,
							false);
				}
			}

			// We're all done drawing, so end the scene.
			driver->endScene();

			int fps = driver->getFPS();

			if (lastFPS != fps) {
				core::stringw str =
						L"Collision detection example - Irrlicht Engine [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;

				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
		}
	}
	device->drop();

}

void pruebaGlobal() {
	// ask user for driver
	/*video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	 if (driverType == video::EDT_COUNT)
	 return 1;
	 */
	// create device
	EventManager receiver;

	IrrlichtDevice* device = createDevice(video::E_DRIVER_TYPE::EDT_OPENGL,
			core::dimension2d<u32>(1280, 720), 16, false, false, false,
			&receiver);




	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	//*** CREACION DEL PERSONAJE ***///
	device->getFileSystem()->addFileArchive(
			"../FateWarriors/models/assassins-creed-altair-obj.zip");
	scene::IAnimatedMesh* meshAltair = smgr->getMesh(
			"assassins-creed-altair.obj");
	scene::ISceneNode* node;
	if (meshAltair) {
		node = smgr->addOctTreeSceneNode(meshAltair->getMesh(0), 0, -1, 1024);
		//node = smgr->addSphereSceneNode();
	}

	/*------CAMARA DE LA ESCENA------*/
	//irr::scene::ICameraSceneNode camera = smgr->addCameraSceneNode(0,core::vector3df(0,0,0),node->getPosition());
	//smgr->addCameraSceneNodeFPS();
	irr::scene::ICameraSceneNode *camera = smgr->addCameraSceneNode(0,
			core::vector3df(0, 180, -60),    //origin
			core::vector3df(node->getPosition().X,  //target
					node->getPosition().Y + 100.f, node->getPosition().Z));

	device->getFileSystem()->addFileArchive(
			"../FateWarriors/media/map-20kdm2.pk3");
	scene::IAnimatedMesh* mesh2 = smgr->getMesh("20kdm2.bsp");
	scene::IMeshSceneNode* node2 = 0;
	//mesh del mapa, nodo del mapa, numero minimo de poligonos
	if (mesh2)
		node2 = smgr->addOctreeSceneNode(mesh2->getMesh(0), 0, -1, 1024);
	//      node = smgr->addMeshSceneNode(mesh->getMesh(0));

	if (node2) {
		node2->setPosition(core::vector3df(-1300, -144, -1249));

		scene::ITriangleSelector* selector = smgr->createOctreeTriangleSelector(
				node2->getMesh(), node2, 128);

		node2->setTriangleSelector(selector);
		if (selector) {
			scene::ISceneNodeAnimator* anim =
					smgr->createCollisionResponseAnimator(selector, camera,
							core::vector3df(30, 50, 30),
							core::vector3df(0, 0, 0),
							core::vector3df(0, 30, 0));
			selector->drop(); //hemos terminado de ajustar y asignar el selector asi que lo dropeamos
			//camera->addAnimator(anim);
			anim->drop(); //de la misma forma al terminar con anim lo dropeamos
		}
		//node2->setMaterialFlag(video::EMF_WIREFRAME, !node2->getMaterial(0).Wireframe);

	}

	if (node) {

		//node = smgr->addSphereSceneNode(10,32,0,0,core::vector3df(100,-50,0),core::vector3df(0,0,0),core::vector3df(1,1,1)); //PRUEBA ESFERICA
		//constante con el radio del espheroid envolviendo a nuestro personaje para calcular las colisiones
		const core::aabbox3d<f32>& box = node->getBoundingBox();
		core::vector3df radius = box.MaxEdge - box.getCenter();

		node->setPosition(core::vector3df(600, -50, 0));
		scene::ITriangleSelector* selector2 =
				smgr->createOctreeTriangleSelector(node2->getMesh(), node2,
						128);

		//node->setMaterialTexture(0, driver->getTexture("../../media/wall.bmp"));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
		node->setTriangleSelector(selector2);
		if (selector2) {
			scene::ISceneNodeAnimator* anim =
					smgr->createCollisionResponseAnimator(selector2, node,
							core::vector3df(30, 50, 30),
							core::vector3df(0, -10, 0),
							core::vector3df(0, 30, 0));
			selector2->drop(); //hemos terminado de ajustar y asignar el selector asi que lo dropeamos
			node->addAnimator(anim);
			anim->drop(); //de la misma forma al terminar con anim lo dropeamos
		}
	}

	//camera->setParent(node);
	//camera->setPosition(core::vector3df(0,180,-60));
	//camera->setRotation(core::vector3df(0,0,0));
	//camera->setTarget(node->getPosition());

	//control orbital de la camara
	float direction = 0;
	float zdirection = 0;
	//camera->setParent(node);

	device->getCursorControl()->setVisible(false);

	device->getGUIEnvironment()->addImage(
			driver->getTexture("../../media/irrlichtlogoalpha2.tga"),
			core::position2d<s32>(10, 20));

	gui::IGUIStaticText* diagnostics =
			device->getGUIEnvironment()->addStaticText(L"",
					core::rect<s32>(10, 10, 400, 20));
	diagnostics->setOverrideColor(video::SColor(255, 255, 255, 0));

	int lastFPS = -1;

	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
	u32 then = device->getTimer()->getTime();

	// This is the movemen speed in units per second.
	const f32 MOVEMENT_SPEED = 200.f;
	core::vector3df nodeRotation;

	while (device->run()) {
		// Work out a frame delta time.
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32) (now - then) / 1000.f; // Time in seconds
		then = now;

		//camera->setTarget(node->getPosition());

		/*****ORBITAL CAMERA******/
		core::position2d<f32> cursorPos =
				device->getCursorControl()->getRelativePosition();
		scene::ICameraSceneNode* camera =
				device->getSceneManager()->getActiveCamera();
		core::vector3df cameraPos = camera->getAbsolutePosition();

		float sensibilidadX = 256.0f; //sensibilidad de la camara en el eje X
		float sensibilidadY = 256.0f; //sensibilidad de la camara en el eje Y

		float change_x = (cursorPos.X - 0.5) * sensibilidadX;
		float change_y = (cursorPos.Y - 0.5) * sensibilidadY;

		direction += change_x; //rotacion de la camara en horizontal
		zdirection -= change_y; //rotacion de la camara en vertical

		unsigned short gradosRotacion = 55; //grados que puede rotar la camara en vertical

		if (zdirection < -gradosRotacion) {
			zdirection = -gradosRotacion;
		}

		else if (zdirection > gradosRotacion) {
			zdirection = gradosRotacion;
		}

		device->getCursorControl()->setPosition(0.5f, 0.5f);
		core::vector3df playerPos = core::vector3df(node->getPosition().X,
				node->getBoundingBox().getCenter().Y, node->getPosition().Z);
		//float xf = playerPos.X - cos(direction * M_PI / 180.0f) * 128.0f;
		float yf = playerPos.Y - sin(zdirection * M_PI / 180.0f) * 128.0f;
		//float zf = playerPos.Z + sin(direction * M_PI / 180.0f) * 128.0f;

		float xf = playerPos.X
				- cos(zdirection * irr::core::PI / 180.0f)
						* cos(direction * irr::core::PI / 180.0f) * 128.0f;
		float zf = playerPos.Z
				+ cos(zdirection * irr::core::PI / 180.0f)
						* sin(direction * irr::core::PI / 180.0f) * 128.0f;

		if (node->getPosition().Y >= 0) { //calculos de la camara para una Y positiva

			camera->setPosition(
					core::vector3df(xf,
							yf + node->getBoundingBox().getCenter().Y, zf));
			camera->setTarget(
					core::vector3df(node->getPosition().X,
							(node->getBoundingBox().getCenter().Y) * 1.5f,
							node->getPosition().Z));
		}

		else { //calculos de la camara para una Y negativa
			camera->setPosition(
					core::vector3df(xf,
							yf - node->getBoundingBox().getCenter().Y
									- node->getPosition().Y, zf));
			camera->setTarget(
					core::vector3df(node->getPosition().X,
							(node->getBoundingBox().getCenter().Y * 0.5),
							node->getPosition().Z));
		}
		//node->setRotation(core::vector3df(0, direction+90, 0)); //usamos la rotacion del raton con un ajuste de 90 grados por el modelado de AC
		/**---------------------**/

		core::vector3df nodePosition = node->getPosition();

		if (receiver.IsKeyDown(irr::KEY_KEY_W)) {
			nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
			//nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime * (float)sin(360.0f - direction);
			//nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime * (float)cos(360.0f - direction);
			nodeRotation = core::vector3df(0, 0, 0);
		}

		else if (receiver.IsKeyDown(irr::KEY_KEY_S)) {
			nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
			nodeRotation = core::vector3df(0, 180, 0);
		}

		if (receiver.IsKeyDown(irr::KEY_KEY_A)) {
			nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
			nodeRotation = core::vector3df(0, -90, 0);
		}

		else if (receiver.IsKeyDown(irr::KEY_KEY_D)) {
			nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
			nodeRotation = core::vector3df(0, 90, 0);
		}

		node->setPosition(nodePosition);
		node->setRotation(nodeRotation);

		/*
		 irr::core::vector3df facing( sin( ( node->getRotation().Y + 90.0f ) * M_PI/180.0f ), 0, cos( ( node->getRotation().Y + 90.0f ) * M_PI/180.0f ) );
		 facing.normalize();
		 irr::core::vector3df newPos = (facing*4.0f) + node->getPosition();
		 //node->setPosition( newPos );
		 */

		driver->beginScene(true, true, video::SColor(255, 113, 113, 133));

		smgr->drawAll(); // draw the 3d scene
		device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)

		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps) {
			core::stringw tmp(L"Movement Example - Irrlicht Engine [");
			tmp += driver->getName();
			tmp += L"] fps: ";
			tmp += fps;

			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
	}

	device->drop();
}
void pruebaEngine() {
	std::cout<<"ME METO"<<std::endl;
	Engine engine(false, 1280, 720); //inicializa el motor usando irrlicht con resolucion 1280x720

	engine.cargaModeloC(
			"../FateWarriors/models/assassins-creed-altair-obj.zip",
			"assassins-creed-altair.obj", false, 0, 0, 0);
	/*
	 engine.cargaModeloC("../FateWarriors/models/EscenarioPruebas.zip",
	 "EscenarioPrueba.obj",false,
	 0,0,0);
	 */
	engine.cargaModeloC(
			"../FateWarriors/models/Gilipollas.zip",
			"ManuManco.obj", false, 0, 0, 0);
	//engine.cargaModelo("../FateWarriors/models/Conjunto.3DS",false,0,0,0);
	//engine.cargaModelo("../FateWarriors/models/Nodo.3DS",false,100,0,0);
	//engine.cargaModelo("../FateWarriors/models/Pasillo.3DS",false,200,0,0);

	//engine.cargaModeloC("../FateWarriors/models/conjunto.zip","conjunto.obj",false,100,0,0);

	engine.Render();
}
int main() {
	pruebaEngine();
	//pruebaCol1();
	//pruebaGlobal();
	return 0;
}
