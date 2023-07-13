class Camera {
    constructor(){
      this.fov = 60;
      this.eye = new Vector3([0, 0, 0]);
      this.at = new Vector3([0, 0, -1]);
      this.up = new Vector3([0, 1, 0]);
  
      this.viewMatrix = new Matrix4();
      this.updateView();
  
      this.projMatrix = new Matrix4();
      this.projMatrix.setPerspective(this.fov, canvas.width / canvas.height, .1, 1000);
  
      this.speed = .3;
      this.alpha = 3;
    }
  
    moveForward(){
      let f = new Vector3();
      f.set(this.at);
      f.sub(this.eye);
      f.normalize();
      f.mul(this.speed);
      this.eye.add(f);
      this.at.add(f);
      this.updateView();
    }
  
    moveBackward(){
      let b = new Vector3();
      b.set(this.eye);
      b.sub(this.at);
      b.normalize();
      b.mul(this.speed);
      this.eye.add(b);
      this.at.add(b);
      this.updateView();
    }
  
    moveLeft(){
      let f = new Vector3();
      f.set(this.at);
      f.sub(this.eye);
      let s = Vector3.cross(this.up, f);
      s.normalize();
      s.mul(this.speed);
      this.eye.add(s);
      this.at.add(s);
      this.updateView();
    }
  
    moveRight(){
      let f = new Vector3();
      f.set(this.at);
      f.sub(this.eye);
      let s = Vector3.cross(f, this.up);
      s.normalize();
      s.mul(this.speed);
      this.eye.add(s);
      this.at.add(s);
      this.updateView();
    }
  
    panLeft(){
      let f = new Vector3();
      f.set(this.at);
      f.sub(this.eye);
      let rotationMatrix = new Matrix4();
      rotationMatrix.setRotate(this.alpha, this.up.elements[0], this.up.elements[1], this.up.elements[2]);
      let f_prime = rotationMatrix.multiplyVector3(f);
      f_prime.add(this.eye);
      this.at = f_prime;
      this.updateView();
    }
  
    panRight(){
      let f = new Vector3();
      f.set(this.at);
      f.sub(this.eye);
      let rotationMatrix = new Matrix4();
      rotationMatrix.setRotate(-this.alpha, this.up.elements[0], this.up.elements[1], this.up.elements[2]);
      let f_prime = rotationMatrix.multiplyVector3(f);
      f_prime.add(this.eye);
      this.at = f_prime;
      this.updateView();
    }
  
    pan(alpha, alpha2) {
      let f = new Vector3();
      f.set(this.at);
      f.sub(this.eye);
      let rotationMatrix = new Matrix4();
      rotationMatrix.setRotate(alpha, this.up.elements[0], this.up.elements[1], this.up.elements[2]);
      let f_prime = rotationMatrix.multiplyVector3(f);
      let d = Vector3.cross(f_prime, this.up);
      rotationMatrix.setRotate(alpha2, d.elements[0], d.elements[1], d.elements[2]);
      let d_prime = rotationMatrix.multiplyVector3(f_prime);
      d_prime.add(this.eye);
      this.at = d_prime;
      this.updateView();
  }
  
    updateView(){
      this.viewMatrix.setLookAt(this.eye.elements[0], this.eye.elements[1], this.eye.elements[2],
                        this.at.elements[0], this.at.elements[1], this.at.elements[2],
                        this.up.elements[0], this.up.elements[1], this.up.elements[2]);
    }
  
  }