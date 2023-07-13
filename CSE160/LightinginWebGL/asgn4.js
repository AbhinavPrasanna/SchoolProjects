//Vertex Shader
var VSHADER_SOURCE =
    'precision mediump float;\n' +
    'attribute vec4 a_Position;\n' +
    'attribute vec2 a_UV;\n' +
    'attribute vec3 a_Normal;\n' +
    'varying vec2 v_UV;\n' +
    'varying vec3 v_Normal;\n' +
    'varying vec4 v_VertPos;\n' +
    'uniform mat4 u_ModelMatrix;\n' +
    'uniform mat4 u_GlobalRotateMatrix;\n' +
    'uniform mat4 u_ViewMatrix;\n' +
    'uniform mat4 u_ProjectionMatrix;\n' +
    'void main() {\n' +
    '  gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_GlobalRotateMatrix * u_ModelMatrix * a_Position;\n' +
    '  v_UV = a_UV;\n' +
    '  v_Normal = a_Normal;\n' +
    '  v_VertPos = u_ModelMatrix * a_Position;\n' +
    '}\n';

// Fragment Shader
var FSHADER_SOURCE =
    'precision mediump float;\n' +
    'uniform vec4 u_FragColor;\n' +
    'varying vec2 v_UV;\n' +
    'varying vec3 v_Normal;\n' +
    'uniform sampler2D u_Sampler0;\n' +
    'uniform sampler2D u_Sampler1;\n' +
    'uniform sampler2D u_Sampler2;\n' +
    'uniform int u_whichTexture;\n' +
    'uniform vec3 u_lightPos;\n' +
    'uniform vec3 u_cameraPos;\n' +
    'uniform vec3 v_VertPos;\n' +
    'uniform bool u_lightOn;\n' +
    'void main() {\n' +
    '  if(u_whichTexture == -3) {\n' +
    '    gl_FragColor = vec4((v_Normal+1.0)/2.0, 1.0);\n' +
    '  } else if (u_whichTexture == -2) {\n' +
    '    gl_FragColor = u_FragColor;\n' +
    '  } else if (u_whichTexture == -1) {\n' +
    '    gl_FragColor = vec4(v_UV, 1.0, 1.0);\n' +
    '  } else if (u_whichTexture == 0) {\n' +
    '    gl_FragColor = texture2D(u_Sampler0, v_UV);\n' +
    '  } else if (u_whichTexture == 1) {\n' +
    '    gl_FragColor = texture2D(u_Sampler1, v_UV);\n' +
    '  } else if (u_whichTexture == 2) {\n' +
    '    gl_FragColor = texture2D(u_Sampler2, v_UV);\n' +
    '  } else {\n' +
    '    gl_FragColor = vec4(1.0, 0.2, 0.2, 1);\n' +
    '  }\n' +
    '  vec3 lightVector = u_lightPos - vec3(v_VertPos);\n' +
    '  float r = length(lightVector);\n' +
    '  vec3 L = normalize(lightVector);\n' +
    '  vec3 N = normalize(v_Normal);\n' +
    '  float nDotL = max(dot(N, L), 0.0);\n' +
    '  vec3 R = reflect(-L, N);\n' +
    '  vec3 E = normalize(u_cameraPos-vec3(v_VertPos));\n' +
    '  float specular = pow(max(dot(E,R),0.0),10.0);\n' +
    '  vec3 diffuse = vec3(gl_FragColor)*nDotL;\n' +
    '  vec3 ambient = vec3(gl_FragColor)*0.3;\n' +
    '  if(u_lightOn){\n' +
    '    if(u_whichTexture == 0 || u_whichTexture == 1 || u_whichTexture == 2){\n' +
    '      gl_FragColor = vec4(diffuse+ambient+specular, 1.0);\n' +
    '    } else {\n' +
    '      gl_FragColor = vec4(diffuse+ambient, 1.0);\n' +
    '    }\n' +
    ' }\n' +
    '}\n';

//Global Variables
var gl;
var canvas;
var a_Position;
var a_UV;
var image;
var image2;
var matrix;
var texture;
var a_Normal;


//Standard Colors
var black = [0.0, 0.0, 0.0, 1.0];
var white = [1.0, 1.0, 1.0, 1.0];

//Skin Color for Pig
var skin= [0.996, 0.75, 0.793,1.0];
var nostrilcolor = [0.659, 0.490, 0.490,1.0];

//Global Variables for the Shaders
var u_FragColor;
var u_ModelMatrix;
var u_GlobalRotateMatrix;
var u_ViewMatrix;
var u_ProjectionMatrix;
var u_Sampler0;
var u_Sampler1;
var u_Sampler2;
var u_whichTexture;
var u_lightOn;
var u_lightPos;
var u_cameraPos;

//User Interaction Variables
var joint1 = 0; //joint 1 angle
var joint2 = 0;// joint 2 angle
var animation = false;
var headanim = 0;
var g_camera;
var g_globalAngle = 0;
var g_normalon = false;
var g_lightOn = true;
var g_spotLightOn = true;
var g_lightPos = [0, 1, -2];
var g_map = [[4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,],
[4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,],
[4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,],
[4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4,],
[4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,],
[4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,],
[4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,],
[4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,],];
;//Taken from ChatGPT for random map generation with a flat plane
//Animation
var startTime = performance.now()/1000.0;

 //From Previous Assignment
function setupWebGL(){
    canvas = document.getElementById('webgl');
    if(!canvas){
        console.log('Failed to retrieve the <canvas> element');
        return;
    }
    gl = getWebGLContext(canvas , {preserveDrawingBuffer: true}); // taken from Lab 1 Videos
    if(!gl){
        console.log('Failed to get the drawCubeing context for WebGL');
        return;
    }
    gl.enable(gl.DEPTH_TEST);
}

//From Previous Assignment alternated based on the rubric
function connectVariablesToGLSL(){
    if(!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)){
        console.log('Failed to intialize shaders.');
        return;
    }
    a_Position = gl.getAttribLocation(gl.program, 'a_Position');
    if(a_Position < 0){
        console.log('Failed to get the storage location of a_Position');
        return;
    }

    a_UV = gl.getAttribLocation(gl.program, 'a_UV');
    if(a_UV < 0){
        console.log('Failed to get the storage location of a_UV');
        return;
    }
    a_Normal = gl.getAttribLocation(gl.program, 'a_Normal');
    if(a_Normal < 0){
        console.log('Failed to get the storage location of a_Normal');
        return;
    }
    u_FragColor = gl.getUniformLocation(gl.program, 'u_FragColor');
    if(!u_FragColor){
        console.log('Failed to get the storage location of u_FragColor');
        return;
    }
    u_lightPos = gl.getUniformLocation(gl.program, 'u_lightPos');
    if(!u_lightPos){
        console.log('Failed to get the storage location of u_lightPos');
        return;
    }
    u_cameraPos = gl.getUniformLocation(gl.program, 'u_cameraPos');
    if(!u_cameraPos){
        console.log('Failed to get the storage location of u_cameraPos');
        return;
    }
    u_ModelMatrix = gl.getUniformLocation(gl.program, 'u_ModelMatrix');
    if(!u_ModelMatrix){
        console.log('Failed to get the storage location of u_ModelMatrix');
        return;
    }
    u_lightOn = gl.getUniformLocation(gl.program, 'u_lightOn');
    if(!u_lightOn){
        console.log('Failed to get the storage location of u_lightOn');
        return;
    }
    u_GlobalRotateMatrix = gl.getUniformLocation(gl.program, 'u_GlobalRotateMatrix');
    if(!u_GlobalRotateMatrix){
        console.log('Failed to get the storage location of u_GlobalRotateMatrix');
        return;
    }
    u_ViewMatrix = gl.getUniformLocation(gl.program, 'u_ViewMatrix');
    if(!u_ViewMatrix){
        console.log('Failed to get the storage location of u_ViewMatrix');
        return;
    }
    u_ProjectionMatrix = gl.getUniformLocation(gl.program, 'u_ProjectionMatrix');
    if(!u_ProjectionMatrix){
        console.log('Failed to get the storage location of u_ProjectionMatrix');
        return;
    }
    u_Sampler0 = gl.getUniformLocation(gl.program, 'u_Sampler0');
    if(!u_Sampler0){
        console.log('Failed to get the storage location of u_Sampler0');
        return;
    }
    u_Sampler1 = gl.getUniformLocation(gl.program, 'u_Sampler1');
    if(!u_Sampler1){
        console.log('Failed to get the storage location of u_Sampler1');
        return;
    }
    u_Sampler2 = gl.getUniformLocation(gl.program, 'u_Sampler2');
    if(!u_Sampler2){
        console.log('Failed to get the storage location of u_Sampler2');
        return;
    }
    u_whichTexture = gl.getUniformLocation(gl.program, 'u_whichTexture');
    if(!u_whichTexture){
        console.log('Failed to get the storage location of u_whichTexture');
        return;
    }
    matrix = new Matrix4();
    gl.uniformMatrix4fv(u_ModelMatrix, false, matrix.elements);
}

//From the previous assignment alternated based on the rubric
function addActionsForHtmlUI(){
    document.getElementById('normalon').addEventListener('click',function(ev){
        g_normalon = true;
    });
    document.getElementById('normaloff').addEventListener('click',function(ev){
        g_normalon = false;
    });
    document.getElementById('lighton').addEventListener('click',function(ev){
        g_lightOn = true;
    });
    document.getElementById('lightoff').addEventListener('click',function(ev){
        g_lightOn = false;
    });
    document.getElementById('spotlighton').addEventListener('mouseup',function(ev){
        g_spotLightOn = true;
    });
    document.getElementById('spotlightoff').addEventListener('mouseup',function(ev){
        g_spotLightOn = false;
    });
    document.getElementById('xlight').addEventListener('mouseup',function(ev){
        g_lightPos[0] = this.value/100;
        renderScene();
    });
    document.getElementById('ylight').addEventListener('mouseup',function(ev){
        g_lightPos[1] = this.value/100;
        renderScene();
    });
    document.getElementById('zlight').addEventListener('mouseup',function(ev){
        g_lightPos[2] = this.value/100;
        renderScene();
    });
    document.getElementById('cam').addEventListener('mouseup',function(ev){
        g_globalAngle = ev.target.value;
        renderScene();
    });
    document.getElementById('joint1').addEventListener('mouseup',function(ev){
        joint1 = ev.target.value;
        renderScene();
    });
    document.getElementById('joint2').addEventListener('mouseup',function(ev){
        headanim = ev.target.value;
        renderScene();
    });
    document.getElementById('joint4').addEventListener('mouseup',function(ev){
        joint2 = ev.target.value;
        renderScene();
    });
    document.getElementById('on').onclick = function(ev){
        animation = true;
        
    };
    document.getElementById('off').onclick = function(ev){
        animation = false;
    };
}

function initTextures(){
  image = new Image();
  image2 = new Image();
  if(!image){
    console.log('Failed to create the image object');
    return false;
  }
  if(!image2){
    console.log('Failed to create the image object');
    return false;
  }
  image.onload = function(){sendTexturetoGLSL(image,0);};
  image.src = 'images/sky.jpg'
  image2.onload = function(){sendTexturetoGLSL(image2,2);};
  image2.src = 'images/sandstone.jpg'
  return true;
}

function sendTexturetoGLSL(image,imagenum){ //Taken from 3.4 Lab Video
    texture = gl.createTexture();
    if(!texture){
        console.log('Failed to create the texture object');
        return false;
    }
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
    if(imagenum == 0){
        gl.activeTexture(gl.TEXTURE0);
    }
    else if(imagenum == 1){
        gl.activeTexture(gl.TEXTURE1);
    }
    else if(imagenum == 2){
        gl.activeTexture(gl.TEXTURE2);
    }
    gl.bindTexture(gl.TEXTURE_2D, texture);

    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);

    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, image);

    if(imagenum == 0){
        gl.uniform1i(u_Sampler0, 0);
    }
    else if(imagenum == 1){
        gl.uniform1i(u_Sampler1, 1);
    }
    else if(imagenum == 2){
        gl.uniform1i(u_Sampler2, 2);
    }

     
}


//Updated animation function drew inspiration from Lab Videos
function updateAnimation(){
    if(animation){
        joint1 = 30*Math.sin(seconds);
        joint2 = 9.5*Math.sin(seconds);
        headanim= 30*Math.sin(seconds);
    }
    g_lightPos[0] = 5*Math.sin(seconds);
}

//Taken from assignment 2 lab videos
function tick(){
   seconds = performance.now()/1000.0 - startTime;
    updateAnimation();
    renderScene();
    requestAnimationFrame(tick);
}
//FPS Counter taken off ChatGPT. Creates a new div block and sets a fixed fps rate. Uses performance class and record the FPS. As seen in the browser, the website maintains a steady 23 frames per second with occasional dips to 13 frames per second. 
function fps(){
    let fpsCounter = document.createElement('div');
    fpsCounter.style.position = 'fixed';
    fpsCounter.style.top = '10px';
    fpsCounter.style.right = '10px';
    document.body.appendChild(fpsCounter);

    let fps = 0;
    let lastCalledTime = performance.now();
    function updateFPS() {
        requestAnimationFrame(function() {
            let delta = (performance.now() - lastCalledTime) / 1000;
            lastCalledTime = performance.now();
            fps = 1 / delta;
            fpsCounter.textContent = 'FPS: ' + Math.round(fps);
            updateFPS();
        });
}
updateFPS();
}

//Based on previous labs, rubric, and assignment 2 lab video
function main() {
    setupWebGL();
    connectVariablesToGLSL();
    addActionsForHtmlUI();
    document.onkeydown = keydown
    document.onmousemove = moveMouse;
    g_camera = new Camera();
    initTextures();
    gl.clearColor(0, 0, 0, 1);
    requestAnimationFrame(tick);
    fps();
};

function keydown(ev){
    if(ev.keyCode == 65){
        g_camera.moveLeft();
    }
    else if(ev.keyCode == 68){
        g_camera.moveRight();
    }
    else if(ev.keyCode == 69){
        g_camera.panRight();
    }
    else if(ev.keyCode == 81){
       g_camera.panLeft();
    }
    else if(ev. keyCode == 83){
        g_camera.moveBackward();
    }
    else if(ev.keyCode == 87){
        g_camera.moveForward();
    }
    renderScene();
}
function moveMouse(ev){
    if(ev.buttons == 1){
        g_camera.pan(-ev.movementX, -ev.movementY);
    }
    renderScene();
}
function drawMap(){//taken from 3.10 lab video
    for(let x = 0; x<32; x++){
        for(let y=0;y<32;y++){
            var wall = new Cube();
            wall.textureNum = 2;
            wall.matrix.translate(-16+x, 0, -16+y);
            wall.matrix.translate(0,-0.2,0);
            wall.matrix.scale(1,g_map[x][y] - 1,1);
            wall.drawCubeFaster();
        }
    }
}
//Taken from assignment 2 lab videos
function renderScene(){
    gl.uniformMatrix4fv(u_ProjectionMatrix, false, g_camera.projMatrix.elements);


    gl.uniformMatrix4fv(u_ViewMatrix, false, g_camera.viewMatrix.elements);

    var globalRotationMatrix = new Matrix4().rotate(g_globalAngle, 0, 1, 0);
    gl.uniformMatrix4fv(u_GlobalRotateMatrix, false, globalRotationMatrix.elements);

    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gl.clear(gl.COLOR_BUFFER_BIT);

    gl.uniform3f(u_lightPos,g_lightPos[0],g_lightPos[1],g_lightPos[2]);
    gl.uniform3f(u_cameraPos,g_camera.eye.elements[0],g_camera.eye.elements[1],g_camera.eye.elements[2]);

    gl.uniform1i(u_lightOn, g_lightOn);

    var light = new Cube();
    light.color = [1.0,1.0,1.0,1.0];
    light.matrix.translate(g_lightPos[0],g_lightPos[1],g_lightPos[2]);
    light.matrix.scale(-1,-1,-1);
    light.matrix.translate(-0.5,-0.5,-0.5);
    light.drawCube();
    drawMap();
     

    var floor = new Cube();
    floor.color = [1.0,0.0,0.0,1.0];
    floor.textureNum=2;
    floor.matrix.translate(0, -.76, 0.0);
    floor.matrix.scale(200, 0, 200);
    floor.matrix.translate(-.5, 0, -0.5);
    floor.drawCube();

    var sky = new Cube();
    sky.textureNum = 0;
    if(g_normalon== true){ sky.textureNum = -3;}
    sky.matrix.translate(-16, 0, -16);
    sky.matrix.translate(0,-10,0);
    sky.matrix.scale(50,50,50);
    sky.drawCube();

    var sphere = new Sphere();
    sphere.color = [.9, .6, .95, 1];
    sphere.textureNum = 0;
    if(g_normalon==true){sphere.textureNum = -3;}
    sphere.matrix.scale(0.5,0.5,0.5);
    sphere.matrix.translate(2, 1, 0);
    sphere.drawSphere();


var head = new Cube();
head.color = skin;
head.matrix.rotate(headanim, 0, 1, 0);
head.matrix.scale(0.45, 0.45, 0.4);
head.matrix.translate(-.5, 0, -1.25);
head.drawCube();


//Nose and Nostrils

var nose = new Cube();
nose.color = skin;
nose.matrix.rotate(headanim, 0, 1, 0);
nose.matrix.scale(0.2, 0.1, 0.06);
nose.matrix.translate(-0.52, 1.3, -9);
nose.drawCube();

var nostril = new Cube();
nostril.color = nostrilcolor;
nostril.matrix.rotate(headanim, 0, 1, 0);
nostril.matrix.scale(0.05, 0.05, 0.04);
nostril.matrix.translate(-1.99, 2.95, -14);
nostril.drawCube();

var nostril2 = new Cube();
nostril2.color = nostrilcolor;
nostril2.matrix.rotate(headanim, 0, 1, 0);
nostril2.matrix.scale(0.05, 0.05, 0.04);
nostril2.matrix.translate(0.8, 2.95, -14);
nostril2.drawCube();

//Eyes
var lefteye = new Cube();
lefteye.color = white;
lefteye.matrix.rotate(headanim, 0, 1, 0);
lefteye.matrix.scale(0.1, 0.061, 0.04);
lefteye.matrix.translate(-2.1, 3.7,-12.6);
lefteye.drawCube();

var leftpupil = new Cube();
leftpupil.color = black;
leftpupil.matrix.rotate(headanim, 0, 1, 0);
leftpupil.matrix.scale(0.05, 0.061, 0.04);
leftpupil.matrix.translate(-4.3, 3.7, -12.65);
leftpupil.drawCube();

var righteye = new Cube();
righteye.color = white;
righteye.matrix.rotate(headanim, 0, 1, 0);
righteye.matrix.scale(0.1, 0.061, 0.04);
righteye.matrix.translate(1, 3.7, -12.6);
righteye.drawCube();

var rightpupil = new Cube();
rightpupil.color = black;
rightpupil.matrix.rotate(headanim, 0, 1, 0);
rightpupil.matrix.scale(0.05, 0.061, 0.04);
rightpupil.matrix.translate(3, 3.7, -12.65);
rightpupil.drawCube();
//Body
var body = new Cube();
body.color = skin;
body.matrix.scale(.5, 0.4, 0.66);
body.matrix.translate(-.5, 0, -0.25);
body.drawCube();


//Legs
var leftLeg = new Cube();
leftLeg.color = skin;
leftLeg.matrix.setTranslate(0, 0, 0);
leftLeg.matrix.rotate(-joint1, 1, 0, 0); 
leftLeg.matrix.scale(.175, -0.30, 0.175);
leftLeg.matrix.translate(-1.15, -.25, -0.75);
leftLeg.drawCube();

var rightleg = new Cube();
rightleg.color = skin;
rightleg.matrix.setTranslate(0, 0, 0);
rightleg.matrix.rotate(joint1, 1, 0, 0);
rightleg.matrix.scale(.175, -0.30, 0.175);
rightleg.matrix.translate(.2, -.25, -0.75);
rightleg.drawCube();


var leftLegBack = new Cube();
leftLegBack.color = skin;
leftLegBack.matrix.setTranslate(0, 0, 0);
leftLegBack.matrix.rotate(joint2, 1, 0, 0);
leftLegBack.matrix.scale(.175, -0.30, 0.175);
leftLegBack.matrix.translate(-1.15, -.25, 2.3);
leftLegBack.drawCube();

var rightLegBack = new Cube();
rightLegBack.color = skin;
rightLegBack.matrix.setTranslate(0, 0, 0);
rightLegBack.matrix.rotate(-joint2, 1, 0, 0); // Joint 1
rightLegBack.matrix.scale(.175, -0.30, 0.175);
rightLegBack.matrix.translate(.2, -.25, 2.3);
rightLegBack.drawCube();
}

