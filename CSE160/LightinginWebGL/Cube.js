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
        
        drawTriangle3DUVNormal( [0.0,0.0,0.0,  1.0,1.0,0.0,  1.0,0.0,0.0], [0,0, 1,1, 1,0], [0,0,-1, 0,0,-1, 0,0,-1]);
        drawTriangle3DUVNormal( [0.0,0.0,0.0,  0.0,1.0,0.0,  1.0,1.0,0.0], [0,0, 0,1, 1,1], [0,0,-1, 0,0,-1, 0,0,-1] );

      drawTriangle3DUVNormal( [0,1,0,  1,1,1,  1,1,0], [0,0, 1,1, 1,0], [0,1,0, 0,1,0, 0,1,0]);
      drawTriangle3DUVNormal( [0,1,0,  0,1,1,  1,1,1], [0,0, 0,1, 1,1], [0,1,0, 0,1,0, 0,1,0]);

      drawTriangle3DUVNormal( [1,0,0,  1,1,0,  1,1,1], [0,0, 0,1, 1,1], [1,0,0, 1,0,0, 1,0,0]);
      drawTriangle3DUVNormal( [1,0,0,  1,1,1,  1,0,1], [0,0, 1,1, 1,0], [1,0,0, 1,0,0, 1,0,0]);

      drawTriangle3DUVNormal( [0,0,0,  0,0,1,  1,0,1], [0,0, 0,1, 1,1], [0,-1,0, 0,-1,0, 0,-1,0]);
      drawTriangle3DUVNormal( [0,0,0,  1,0,1,  1,0,0], [0,0, 1,1, 1,0], [0,-1,0, 0,-1,0, 0,-1,0]);

      drawTriangle3DUVNormal( [0,0,0,  0,1,0,  0,1,1], [0,0, 0,1, 1,1], [-1,0,0, -1,0,0, -1,0,0]);
      drawTriangle3DUVNormal( [0,0,0,  0,1,1,  0,0,1], [0,0, 1,1, 1,0], [-1,0,0, -1,0,0, -1,0,0]);
      
      drawTriangle3DUVNormal( [0.0,0.0,1.0,  1.0,1.0,1.0,  1.0,0.0,1.0], [0,0, 1,1, 1,0], [0,0,1, 0,0,1, 0,0,1]);
      drawTriangle3DUVNormal( [0.0,0.0,1.0,  0.0,1.0,1.0,  1.0,1.0,1.0], [0,0, 0,1, 1,1], [0,0,1, 0,0,1, 0,0,1]);
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
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.DYNAMIC_DRAW);
  
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

    var normalBuffer = gl.createBuffer();
    if (!normalBuffer) {
        console.log('Failed to create the buffer object');
        return -1;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, normalBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.DYNAMIC_DRAW);
    gl.vertexAttribPointer(a_Normal, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(a_Normal);


    // Draw the  triangle
    gl.drawArrays(gl.TRIANGLES, 0, n);
 }

 function drawTriangle3DUVNormal(vertices,uv,normal){
    var n = vertices.length / 3;
    var vertexBuffer = gl.createBuffer();
    if (!vertexBuffer) {
        console.log('Failed to create the buffer object');
        return -1;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.DYNAMIC_DRAW);
    gl.vertexAttribPointer(a_Position, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(a_Position);
    var uvBuffer = gl.createBuffer();
    if (!uvBuffer) {
        console.log('Failed to create the buffer object');
        return -1;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, uvBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(uv), gl.DYNAMIC_DRAW);
    gl.vertexAttribPointer(a_UV, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(a_UV);
    var normalBuffer = gl.createBuffer();
    if (!normalBuffer) {
        console.log('Failed to create the buffer object');
        return -1;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, normalBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normal), gl.DYNAMIC_DRAW);
    gl.vertexAttribPointer(a_Normal, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(a_Normal);
    gl.drawArrays(gl.TRIANGLES, 0, n);


 }