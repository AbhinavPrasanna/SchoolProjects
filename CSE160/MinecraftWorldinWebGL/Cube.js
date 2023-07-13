class Cube{
    //Base Cube Constructor taken off video
    constructor(){
        this.color = [0, 0, 0, 1];
        this.matrix = new Matrix4();
        this.textureNum = -2;
        this.vertices = new Float32Array([ //Taken off 3.11 Lab Video
                0,0,0,  1,1,0,  1,0,0,
                0,0,0,  0,1,0,  1,1,0,
                0,1,0,  1,1,1,  1,1,0,
                0,1,0,  0,1,1,  1,1,1,
                1,0,0,  1,1,0,  1,1,1,
                1,0,0,  1,1,1,  1,0,1,
                0,0,0,  0,0,1,  1,0,1,
                0,0,0,  1,0,1,  1,0,0,
                0,0,0,  0,1,0,  0,1,1,
                0,0,0,  0,1,1,  0,0,1,
                0,0,1,  1,1,1,  1,0,1,
                0,0,1,  0,1,1,  1,1,1
              ] );
        this.UVs = new Float32Array([ //Taken off 3.11 Lab Video
                0,0,  1,1,  1,0,
                0,0,  0,1,  1,1,
                0,0, 1,1, 1,0,
                0,0, 0,1, 1,1,
                0,0, 0,1, 1,1,
                0,0, 1,1, 1,0,
                0,0, 0,1, 1,1,
                0,0, 1,1, 1,0,
                0,0, 0,1, 1,1,
                0,0, 1,1, 1,0,
                0,0, 1,1, 1,0,
                0,0, 0,1, 1,1
            ]);
                
    }
    //Alternated but base method taken from Lecture Videos on Assignment 2
    drawCube(mat){
        if(!mat){
            mat = this.matrix;
        }
        var rgba = this.color;                                           
        
        gl.uniform1i(u_whichTexture, this.textureNum);
        gl.uniform4f(u_FragColor, rgba[0], rgba[1], rgba[2], rgba[3]);  
        gl.uniformMatrix4fv(u_ModelMatrix, false, this.matrix.elements);
        
        drawTriangle3DUV([0,0,0,  1,1,0,  1,0,0], [0,0, 1,1, 1,0]);
        drawTriangle3DUV([0,0,0,  0,1,0,  1,1,0], [0,0, 0,1, 1,1]);

        gl.uniform4f(u_FragColor, rgba[0]*.9, rgba[1]*.9, rgba[2]*.9, rgba[3]);
        drawTriangle3DUV([0,1,0,  1,1,1,  1,1,0], [0,0, 1,1, 1,0]);
        drawTriangle3DUV([0,1,0,  0,1,1,  1,1,1], [0,0, 0,1, 1,1]);

        gl.uniform4f(u_FragColor, rgba[0]*.9, rgba[1]*.9, rgba[2]*.9, rgba[3]);
        drawTriangle3DUV([0,0,0,  1,0,1,  0,0,1], [0,0, 1,1, 1,0]);
        drawTriangle3DUV([0,0,0,  1,0,0,  1,0,1], [0,0, 0,1, 1,1]);

        
        gl.uniform4f(u_FragColor, rgba[0]*.8, rgba[1]*.8, rgba[2]*.8, rgba[3]);
        drawTriangle3DUV([1,0,0,  1,1,1,  1,1,0], [0,0, 1,1, 1,0]);
        drawTriangle3DUV([1,0,0,  1,0,1,  1,1,1], [0,0, 0,1, 1,1]);


        gl.uniform4f(u_FragColor, rgba[0]*.8, rgba[1]*.8, rgba[2]*.8, rgba[3]);
        drawTriangle3DUV([0,0,0,  0,1,1,  0,1,0], [0,0, 1,1, 1,0]);
        drawTriangle3DUV([0,0,0,  0,0,1,  0,1,1], [0,0, 0,1, 1,1]);

    
        gl.uniform4f(u_FragColor, rgba[0]*.7, rgba[1]*.7, rgba[2]*.7, rgba[3]);
        drawTriangle3DUV([0,0,1,  1,1,1,  0,1,1], [0,0, 1,1, 1,0]);
        drawTriangle3DUV([0,0,1,  1,0,1,  1,1,1], [0,0, 0,1, 1,1]);
    }
    drawCubeFaster(mat){ //Taken off 3.12 Lab Vidoe
        if(!mat){
            mat = this.matrix;
        }
        var rgba = this.color;
     gl.uniform1i(u_whichTexture, this.textureNum);
 
     gl.uniform4f(u_FragColor, rgba[0], rgba[1], rgba[2], rgba[3]);

     gl.uniformMatrix4fv(u_ModelMatrix, false, this.matrix.elements);
     drawTriangle3DUV(this.vertices, this.UVs);
    }

}
 function drawTriangle3DUV(vertices,uv){//Function taken off 2.1 video and copied over to make this UV function
    var n = vertices.length / 3; 
  
    // Create a buffer object
    var vertexBuffer = gl.createBuffer();
    if (!vertexBuffer) {
      console.log('Failed to create the buffer object');
      return -1;
    }
  
    // Bind the buffer object to target
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    // Write date into the buffer object
    //gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.DYNAMIC_DRAW);
  
   // var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
    //if (a_Position < 0) {
   //   console.log('Failed to get the storage location of a_Position');
   //   return -1;
    //}
    // Assign the buffer object to a_Position variable
    gl.vertexAttribPointer(a_Position, 3, gl.FLOAT, false, 0, 0);
  
    // Enable the assignment to a_Position variable
    gl.enableVertexAttribArray(a_Position);
  

    // Create a buffer object for UV
    var uvBuffer = gl.createBuffer();
    if (!uvBuffer) {
      console.log('Failed to create the buffer object');
      return -1;
    }

    // Bind the buffer object to target
    gl.bindBuffer(gl.ARRAY_BUFFER, uvBuffer);

    // Write data into the buffer object
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(uv), gl.DYNAMIC_DRAW);

    // Assign the buffer object to a_Position variable
    gl.vertexAttribPointer(a_UV, 2, gl.FLOAT, false, 0, 0);

    // Enable the assignment to a_Position variable
    gl.enableVertexAttribArray(a_UV);


    // Draw the  triangle
    gl.drawArrays(gl.TRIANGLES, 0, n);
 }