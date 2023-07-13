function sin(x){
    return Math.sin(x);
}
function cos(x){
    return Math.cos(x);
}

class Sphere{
    constructor(){
        this.color = [1, 1, 1, 1];
        this.matrix = new Matrix4();
        this.textureNum = -2;
        this.vertices = new Float32Array([ //Copied from Cube.js
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
      this.UVs = new Float32Array([ //Copied from Cube.js
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
      ] );
      this.normals = new Float32Array([ //Taken from 4.4 Lab Vidoe
      0,0,-1, 0,0,-1, 0,0,-1,
          0,0,-1, 0,0,-1, 0,0,-1,
          0,1,0, 0,1,0, 0,1,0, 
          0,1,0, 0,1,0, 0,1,0, 
          1,0,0, 1,0,0, 1,0,0,
          1,0,0, 1,0,0, 1,0,0,
          0,-1,0, 0,-1,0, 0,-1,0,
          0,-1,0, 0,-1,0, 0,-1,0,
          -1,0,0, -1,0,0, -1,0,0,
          -1,0,0, -1,0,0, -1,0,0,
          0,0,1, 0,0,1, 0,0,1,
          0,0,1, 0,0,1, 0,0,1
        ]);
    }
    drawSphere(){
        var rgba = this.color;
        gl.uniform4f(u_FragColor, rgba[0], rgba[1], rgba[2], rgba[3]);
        gl.uniformMatrix4fv(u_ModelMatrix, false, this.matrix.elements);
        /*Code below taken straight from 3.4 Lab Video with changed coordinates*/
        var dd = Math.PI / 10;
        var p1, p2, p3, p4;
        var uv1, uv2, uv3, uv4;

        for(var t=0;t<Math.PI;t+=(Math.PI/10)){
            for(var r=0; r<(2*Math.PI); r+=(Math.PI/10)){
                    p1 = [sin(t)*cos(r), sin(t)*sin(r), cos(t)];
                    p2 = [sin(t+dd)*cos(r), sin(t+dd)*sin(r), cos(t+dd)];
                    p3 = [sin(t)*cos(r+dd), sin(t)*sin(r+dd), cos(t)];
                    p4 = [sin(t+dd)*cos(r+dd), sin(t+dd)*sin(r+dd), cos(t+dd)];

                    uv1 = [t/(Math.PI), r/(2*Math.PI)];
                    uv2 = [(t+dd)/(Math.PI), r/(2*Math.PI)];
                    uv3 = [t/(Math.PI), (r+dd)/(2*Math.PI)];
                    uv4 = [(t+dd)/(Math.PI), (r+dd)/(2*Math.PI)];

                    var v = [];
                    var uv = [];
                    v = v.concat(p1);
                    uv = uv.concat(uv1);
                    v = v.concat(p2);
                    uv = uv.concat(uv2);
                    v = v.concat(p4);
                    uv = uv.concat(uv4);
                    gl.uniform4f(u_FragColor, 1,1,1,1);
                    drawTriangle3DUVNormal(v, uv, v);

                    v = [];
                    uv = [];
                    v = v.concat(p1);
                    uv = uv.concat(uv1);
                    v = v.concat(p4);
                    uv = uv.concat(uv4);
                    v = v.concat(p3);
                    uv = uv.concat(uv3);
                    gl.uniform4f(u_FragColor, 1,1,1,1);
                    drawTriangle3DUVNormal(v, uv, v);

            }
        }
    }
    drawSphereFaster(mat){ //Taken off 3.12 Lab Vidoe
        if(!mat){
            mat = this.matrix;
        }
        var rgba = this.color;
     gl.uniform1i(u_whichTexture, this.textureNum);
 
     gl.uniform4f(u_FragColor, rgba[0], rgba[1], rgba[2], rgba[3]);

     gl.uniformMatrix4fv(u_ModelMatrix, false, this.matrix.elements);
     drawTriangle3DUVNormal(this.cubeVerts32, this.UVs, this.Normals);
    }
}