import * as THREE from 'https://cdn.jsdelivr.net/npm/three@0.118/build/three.module.js';

import {OrbitControls} from 'https://cdn.jsdelivr.net/npm/three@0.118/examples/jsm/controls/OrbitControls.js';
import {MTLLoader} from 'https://cdn.jsdelivr.net/npm/three@0.118/examples/jsm/loaders/MTLLoader.js';
import { OBJLoader } from 'https://cdn.jsdelivr.net/npm/three@0.118/examples/jsm/loaders/OBJLoader.js';
import { GLTFLoader } from 'https://cdn.jsdelivr.net/npm/three@0.118/examples/jsm/loaders/GLTFLoader.js';

//Followed this tutorial for 3JS from this video https://www.youtube.com/watch?v=PPwR7h5SnOE&list=PLRL3Z3lpLmH0aqLDbfh0ZmnDkpXPDnTau&index=1&ab_channel=SimonDev using this GitHub Repoisitory:https://github.com/simondevyoutube/ThreeJS_Tutorial_BasicWorld 

class BasicWorldDemo {
  constructor() {
    this._Initialize();
  }

  _Initialize() {
    this._threejs = new THREE.WebGLRenderer({
      antialias: true,
    });
    this._threejs.shadowMap.enabled = true;
    this._threejs.shadowMap.type = THREE.PCFSoftShadowMap;
    this._threejs.setPixelRatio(window.devicePixelRatio);
    this._threejs.setSize(window.innerWidth, window.innerHeight);

    document.body.appendChild(this._threejs.domElement);

    window.addEventListener('resize', () => {
      this._OnWindowResize();
    }, false);

    const fov = 60;
    const aspect = 1920 / 1080;
    const near = 1.0;
    const far = 1000.0;
    this._camera = new THREE.PerspectiveCamera(fov, aspect, near, far);
    this._camera.position.set(75, 20, 0);

    this._scene = new THREE.Scene();

    //Directional Light on the Map
    let light = new THREE.SpotLight(0xffa95c,4); // Retrieved from this video: https://www.youtube.com/watch?v=7GGNzryHfTw&ab_channel=RedStapler
    light.position.set(-1000,1000,1000);
    light.castShadow = true;
    light.position.set( 
      this._camera.position.x + 10,
      this._camera.position.y + 10,
      this._camera.position.z + 10,
    );
    this._scene.add( light );

    //Shadows coded with this video: https://www.youtube.com/watch?v=AUF15I3sy6s&list=RDCMUCEwhtpXrg5MmwlH04ANpL8A&index=13&ab_channel=SimonDev
    //Cameras coded with this video: https://www.youtube.com/watch?v=FwcXultcBl4&list=RDCMUCEwhtpXrg5MmwlH04ANpL8A&index=7&ab_channel=SimonDev
    //Basic Fog code taken from this video: https://www.youtube.com/watch?v=k1zGz55EqfU&list=RDCMUCEwhtpXrg5MmwlH04ANpL8A&index=17&ab_channel=SimonDev
    
    light = new THREE.DirectionalLight(0xFFFFFF, 1.0);
    light.position.set(100, 100, 10);
    light.target.position.set(0, 20, 0);
    light.castShadow = true;
    light.shadow.bias = -0.001;
    light.shadow.mapSize.width = 500
    light.shadow.mapSize.height = 500;
    light.shadow.camera.near = 0.1;
    light.shadow.camera.far = 500.0;
    light.shadow.camera.near = 0.5;
    light.shadow.camera.far = 500.0;
    light.shadow.camera.left = 100;
    light.shadow.camera.right = -100;
    light.shadow.camera.top = 100;
    light.shadow.camera.bottom = -100;
    this._scene.add(light);



    let light2 = new THREE.RectAreaLight(0xFFFFFF, 8.0, 12.0, 8.0);
    light2.position.set(0, 10, 0);
    light2.lookAt(0, 0, 0);
    this._scene.add(light2);

    //Ambient Light on the Map
    let light3 = new THREE.AmbientLight(0x101010);
    this._scene.add(light3);

    //Fog on the Map
    const color = 0x333333;  //Retrieved from this video: 
    this._scene.fog = new THREE.Fog(color, 10, 130);

    const controls = new OrbitControls(
      this._camera, this._threejs.domElement);
    controls.target.set(0, 20, 0);
    controls.update();

    const loader = new THREE.CubeTextureLoader();
    const text = new THREE.TextureLoader();
    const texture = loader.load([
        './resources/posx.png',
        './resources/negx.png',
        './resources/posy.png',
        './resources/negy.png',
        './resources/posz.png',
        './resources/negz.png',
    ]);
    this._scene.background = texture;

    const plane = new THREE.Mesh(
        new THREE.PlaneGeometry(100, 100, 10, 10),
        new THREE.MeshStandardMaterial({
            map: text.load('./resources/grass.jpeg'),
            side: THREE.DoubleSide,
          }));
    plane.castShadow = false;
    plane.receiveShadow = true;
    plane.rotation.x = -Math.PI / 2;
    this._scene.add(plane);
    const boxgeo = new THREE.BoxGeometry(10, 10, 10);
    var cubematerials = [
      new THREE.MeshBasicMaterial({map: text.load('./resources/minecraftdirt.jpeg'), side: THREE.DoubleSide}), //right
      new THREE.MeshBasicMaterial({map: text.load('./resources/minecraftdirt.jpeg'), side: THREE.DoubleSide}), //left
      new THREE.MeshBasicMaterial({map: text.load('./resources/grass.jpeg'), side: THREE.DoubleSide}), //top
      new THREE.MeshBasicMaterial({map: text.load('./resources/grass.jpeg'), side: THREE.DoubleSide}), //bottom
      new THREE.MeshBasicMaterial({map: text.load('./resources/minecraftdirt.jpeg'), side: THREE.DoubleSide}), //front
      new THREE.MeshBasicMaterial({map: text.load('./resources/minecraftdirt.jpeg'), side: THREE.DoubleSide}), //back

    ];
    var diamondmaterials = [
      new THREE.MeshBasicMaterial({map: text.load('./resources/diamondblock.png'), side: THREE.DoubleSide}), //right
      new THREE.MeshBasicMaterial({map: text.load('./resources/diamondblock.png'), side: THREE.DoubleSide}), //left
      new THREE.MeshBasicMaterial({map: text.load('./resources/diamondblock.png'), side: THREE.DoubleSide}), //top
      new THREE.MeshBasicMaterial({map: text.load('./resources/diamondblock.png'), side: THREE.DoubleSide}), //bottom
      new THREE.MeshBasicMaterial({map: text.load('./resources/diamondblock.png'), side: THREE.DoubleSide}), //front
      new THREE.MeshBasicMaterial({map: text.load('./resources/diamondblock.png'), side: THREE.DoubleSide}), //back
    ];
    var glowstonematerials = [
      new THREE.MeshBasicMaterial({map: text.load('./resources/glowstone.png'), side: THREE.DoubleSide}), //right
      new THREE.MeshBasicMaterial({map: text.load('./resources/glowstone.png'), side: THREE.DoubleSide}), //left
      new THREE.MeshBasicMaterial({map: text.load('./resources/glowstone.png'), side: THREE.DoubleSide}), //top
      new THREE.MeshBasicMaterial({map: text.load('./resources/glowstone.png'), side: THREE.DoubleSide}), //bottom
      new THREE.MeshBasicMaterial({map: text.load('./resources/glowstone.png'), side: THREE.DoubleSide}), //front
      new THREE.MeshBasicMaterial({map: text.load('./resources/glowstone.png'), side: THREE.DoubleSide}), //back
    ]
    var wall = [];
    for(var i = 45; i > 0; i-=10){
      const box = new THREE.Mesh(boxgeo, cubematerials);//Used this video for texturing: https://www.youtube.com/watch?v=l77yAZ0E950&ab_channel=SonarSystems
      const box2 = new THREE.Mesh(boxgeo, cubematerials);
      const box3 = new THREE.Mesh(boxgeo, cubematerials);
      const box4 = new THREE.Mesh(boxgeo, cubematerials);
      const box5 = new THREE.Mesh(boxgeo, cubematerials);
      const box6 = new THREE.Mesh(boxgeo, cubematerials);
      const box7 = new THREE.Mesh(boxgeo, cubematerials);
      const box8 = new THREE.Mesh(boxgeo, cubematerials);
      box.position.set(45, 5.1, -i);
      box2.position.set(i, 5.1, -45);
      box3.position.set(-i, 5.1, -45);
      box4.position.set(45, 5.1, i);
      box5.position.set(-45, 5.1, i);
      box6.position.set(-45, 5.1, -i);
      box7.position.set(i, 5.1, 45);
      box8.position.set(-i, 5.1, 45);
      box.castShadow = true;
      box2.castShadow = true;
      box3.castShadow = true;
      box4.castShadow = true;
      box5.castShadow = true;
      box6.castShadow = true;
      box7.castShadow = true;
      box8.castShadow = true;
      box.receiveShadow = true;
      box2.receiveShadow = true;
      box3.receiveShadow = true;
      box4.receiveShadow = true;
      box5.receiveShadow = true;
      box6.receiveShadow = true;
      box7.receiveShadow = true;
      box8.receiveShadow = true;
      wall.push(box);
      wall.push(box2);
      wall.push(box3);
      wall.push(box4);
      wall.push(box5);
      wall.push(box6);
      wall.push(box7);
      wall.push(box8);
    }

    for(var i = 0; i < wall.length; i++){
      this._scene.add(wall[i]);
    }
    const box = new THREE.Mesh(boxgeo, cubematerials);
    const box2 = new THREE.Mesh(boxgeo, cubematerials);
    const box3 = new THREE.Mesh(boxgeo, cubematerials);
    const box4 = new THREE.Mesh(boxgeo, cubematerials);
    const box5 = new THREE.Mesh(boxgeo, cubematerials);
    const diamondblock = new THREE.Mesh(boxgeo, diamondmaterials);
    const diamondblock2 = new THREE.Mesh(boxgeo, glowstonematerials);
    const diamondblock3 = new THREE.Mesh(boxgeo, glowstonematerials);
    const diamondblock4 = new THREE.Mesh(boxgeo, glowstonematerials);
    const diamondblock5 = new THREE.Mesh(boxgeo, glowstonematerials);
    box.position.set(0, 5.1, 0);
    box2.position.set(10, 5.1, 0);
    box3.position.set(-10, 5.1, 0);
    box4.position.set(0, 5.1, 10);
    box5.position.set(0, 5.1, -10);
    diamondblock.position.set(0, 5.1, 0);
    diamondblock2.position.set(10, 5.1, 10);
    diamondblock3.position.set(-10, 5.1, -10);
    diamondblock4.position.set(-10, 5.1, 10);
    diamondblock5.position.set(10, 5.1, -10);
    box.castShadow = true;
    box2.castShadow = true;
    box3.castShadow = true;
    box4.castShadow = true;
    box5.castShadow = true;
    diamondblock.castShadow = true;
    box.receiveShadow = true;
    box2.receiveShadow = true;
    box3.receiveShadow = true;
    box4.receiveShadow = true;
    box5.receiveShadow = true;
    diamondblock.receiveShadow = true;
    this._scene.add(box);
    this._scene.add(box2);
    this._scene.add(box3);
    this._scene.add(box4);
    this._scene.add(box5);
    this._scene.add(diamondblock);
    this._scene.add(diamondblock2);
    this._scene.add(diamondblock3);
    this._scene.add(diamondblock4);
    this._scene.add(diamondblock5);

    const iso = new THREE.Mesh(
      new THREE.IcosahedronBufferGeometry(5),
      new THREE.MeshStandardMaterial({
        map: text.load('./resources/endblock.png'),
      }));


    iso.position.set(0, 20, 0);
    this._scene.add(iso);
    this._iso = iso;
    const pillar = new THREE.Mesh(
      new THREE.CylinderGeometry(3.5, 3.5, 25, 10),
      new THREE.MeshStandardMaterial({
        map: text.load('./resources/column.jpg'),
      }));
    const pillar2 = new THREE.Mesh(
        new THREE.CylinderGeometry(3.5, 3.5, 25, 10),
        new THREE.MeshStandardMaterial({
          map: text.load('./resources/column.jpg'),
      }));
    const pillar3 = new THREE.Mesh(
        new THREE.CylinderGeometry(3.5, 3.5, 25, 10),
        new THREE.MeshStandardMaterial({
          map: text.load('./resources/column.jpg'),
    }));
    const pillar4 = new THREE.Mesh(
      new THREE.CylinderGeometry(3.5, 3.5, 25, 10),
      new THREE.MeshStandardMaterial({
        map: text.load('./resources/column.jpg'),
    }));
    pillar.position.set(20, 13, 0);
    pillar2.position.set(-20, 13, 0);
    pillar3.position.set(0, 13, 20);
    pillar4.position.set(0,13, -20);
    pillar.castShadow = true;
    pillar2.castShadow = true;
    pillar3.castShadow = true;
    pillar4.castShadow = true;
    pillar.receiveShadow = true;
    pillar2.receiveShadow = true;
    pillar3.receiveShadow = true;
    pillar4.receiveShadow = true;
    this._scene.add(pillar);
    this._scene.add(pillar2);
    this._scene.add(pillar3);
    this._scene.add(pillar4);

    // for (let x = 0; x < 8; x++) {
    //   for (let y = 0; y < 8; y++) {
    //     const box = new THREE.Mesh(
    //       new THREE.SphereBufferGeometry(.5, 32, 16),
    //       new THREE.MeshStandardMaterial({
    //           color: 0x808080,
    //       }));
    //     box.position.set(-16+x, Math.random() * 4.0 + 2.0, -16+y);
    //     box.castShadow = true;
    //     box.receiveShadow = true;
    //     this._scene.add(box);
    //   }
    // }

    this._LoadModel();
    this._RAF();
  }

  _LoadModel() {
    const loader = new GLTFLoader();
    loader.load('./resources/minecraft_-_steve/scene.gltf', (gltf) => { // retrieved from this video: https://www.youtube.com/watch?v=8n_v1aJmLmc&t=257s&ab_channel=SimonDev
      gltf.scene.traverse(c => {
        c.castShadow = true;
        c.receiveShadow = true;
      });
       
      gltf.scene.scale.set(0.5, 0.5 , 0.5);
      gltf.scene.position.set(20, 8, -30);
      gltf.scene.rotation.y = Math.PI/2;
      this._scene.add(gltf.scene);
    });
    const loader2 = new GLTFLoader();
    loader2.load('./resources/minecraft_-_sheep/scene.gltf', (gltf) => {
      gltf.scene.traverse(c => {
        c.castShadow = true;
        c.receiveShadow = true;
      });
      gltf.scene.scale.set(0.5, 0.5 , 0.5);
      gltf.scene.position.set(-30, 6, -20);
      this._scene.add(gltf.scene);
    });
    const loader3 = new GLTFLoader();
    loader3.load('./resources/minecraft_-_pig/scene.gltf', (gltf) => {
      gltf.scene.traverse(c => {
        c.castShadow = true;
        c.receiveShadow = true;
      });
      gltf.scene.scale.set(0.5, 0.5 , 0.5);
      gltf.scene.position.set(20, 4, 20);
      gltf.scene.rotation.y = Math.PI/2;
      this._scene.add(gltf.scene);
    });
    const loader4 = new GLTFLoader();
    loader4.load('./resources/minecraft_-_wolf/scene.gltf', (gltf) => {
      gltf.scene.traverse(c => {
        c.castShadow = true;
        c.receiveShadow = true;
      });
      gltf.scene.scale.set(0.5, 0.5 , 0.5);
      gltf.scene.position.set(0, 4, 30);
      gltf.scene.rotation.y = Math.PI/-0.75;
      this._scene.add(gltf.scene);
    });

    
  }


  _OnWindowResize() {
    this._camera.aspect = window.innerWidth / window.innerHeight;
    this._camera.updateProjectionMatrix();
    this._threejs.setSize(window.innerWidth, window.innerHeight);
  }

  _RAF() {
    requestAnimationFrame(() => {
      this._iso.rotation.y += 0.1;
      this._iso.rotation.x += 0.1;
      this._iso.rotation.z += 0.1;
      this._threejs.render(this._scene, this._camera);
      this._RAF();
    });
  }
}


let _APP = null;

window.addEventListener('DOMContentLoaded', () => {
  _APP = new BasicWorldDemo();
});
