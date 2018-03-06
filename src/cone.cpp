vector<Point*> drawCone(float radius, float height, int slices, int stacks) {
    vector<Point*> pointsList;
    double alpha = (2*M_PI)/slices;
    double tmp = height/stacks;
    double tanB = height/radius;
    double h1 = 0, h2, radius2;
    double xc1, zc1, xc2, zc2, xc3, zc3, xc4, zc4;

    for(int j=1; j<=stacks; j++){
        h2 = tmp * j;
        radius2 = (height-h2) / tanB;
        xc1 = radius, zc1 = 0;
        xc3 = radius2, zc3 = 0;

        if(j == 1){
            for(int i=1; i<=slices+1; i++){
                xc2 = radius * sin(i * alpha);
                zc2 = radius * cos(i * alpha);
                xc4 = radius2 * sin(i * alpha);
                zc4 = radius2 * cos(i * alpha);

                glBegin(GL_TRIANGLES);
                //base
                pointsList.push_back(new Point(xc1,0.0f,zc1));
                pointsList.push_back(new Point(0.0f,0.0f,0.0f));
                pointsList.push_back(new Point(xc2,0.0f,zc2));
                //lados
                pointsList.push_back(new Point(xc1,0.0f,zc1));
                pointsList.push_back(new Point(xc2,0.0f,zc2));
                pointsList.push_back(new Point(xc3,h2,zc3));
                pointsList.push_back(new Point(xc2,0.0f,zc2));
                pointsList.push_back(new Point(xc4,h2,zc4));
                pointsList.push_back(new Point(xc3,h2,zc3));
                glEnd();

                xc1 = xc2, zc1 = zc2;
                xc3 = xc4, zc3 = zc4;
            }
        }
        else if(j == stacks){
            for(int i=1; i<=slices+1; i++){
                xc2 = radius * sin(i * alpha);
                zc2 = radius * cos(i * alpha);

                glBegin(GL_TRIANGLES);
                pointsList.push_back(new Point(0.0f,height,0.0f));
                pointsList.push_back(new Point(xc1,h1,zc1));
                pointsList.push_back(new Point(xc2,h1,zc2));
                glEnd();

                xc1 = xc2, zc1 = zc2;
            }
        }
        else {
            for (int i = 1; i <= slices + 1; i++) {
                xc2 = radius * sin(i * alpha);
                zc2 = radius * cos(i * alpha);
                xc4 = radius2 * sin(i * alpha);
                zc4 = radius2 * cos(i * alpha);

                glBegin(GL_TRIANGLES);
                pointsList.push_back(new Point(xc1, h1, zc1));
                pointsList.push_back(new Point(xc2, h1, zc2));
                pointsList.push_back(new Point(xc3, h2, zc3));
                pointsList.push_back(new Point(xc2, h1, zc2));
                pointsList.push_back(new Point(xc4, h2, zc4));
                pointsList.push_back(new Point(xc3, h2, zc3));
                glEnd();

                xc1 = xc2, zc1 = zc2;
                xc3 = xc4, zc3 = zc4;
            }
        }

        h1 = h2;
        radius = radius2;
    }
    
    return pointsList;
}






void drawCone(float radius, float height, int slices, int stacks) {
    double alpha = (2*M_PI)/slices;
    float cor1, cor2;
    double tmp = height/stacks;
    double tanB = height/radius;
    double h1 = 0, h2, radius2;
    double xc1, zc1, xc2, zc2, xc3, zc3, xc4, zc4;

    for(int j=1; j<=stacks; j++){
        h2 = tmp * j;
        radius2 = (height-h2) / tanB;
        xc1 = radius, zc1 = 0;
        xc3 = radius2, zc3 = 0;

        if(j == 1){
            for(int i=1; i<=slices+1; i++){
                xc2 = radius * sin(i * alpha);
                zc2 = radius * cos(i * alpha);
                xc4 = radius2 * sin(i * alpha);
                zc4 = radius2 * cos(i * alpha);
                cor1 = ((float) rand()) / (float) RAND_MAX;
                cor2 = ((float) rand()) / (float) RAND_MAX;

                glBegin(GL_TRIANGLES);
                //base
                glColor3f(0.0f,cor2,cor1);
                glVertex3f(xc1,0.0f,zc1);
                glVertex3f(0.0f,0.0f,0.0f);
                glVertex3f(xc2,0.0f,zc2);
                //lados
                glVertex3f(xc1,0.0f,zc1);
                glVertex3f(xc2,0.0f,zc2);
                glVertex3f(xc3,h2,zc3);
                glVertex3f(xc2,0.0f,zc2);
                glVertex3f(xc4,h2,zc4);
                glVertex3f(xc3,h2,zc3);
                glEnd();

                xc1 = xc2, zc1 = zc2;
                xc3 = xc4, zc3 = zc4;
            }
        }
        else if(j == stacks){
            for(int i=1; i<=slices+1; i++){
                xc2 = radius * sin(i * alpha);
                zc2 = radius * cos(i * alpha);
                cor1 = ((float) rand()) / (float) RAND_MAX;
                cor2 = ((float) rand()) / (float) RAND_MAX;

                glBegin(GL_TRIANGLES);
                glColor3f(cor2,0.0f,cor1);
                glVertex3f(0.0f,height,0.0f);
                glVertex3f(xc1,h1,zc1);
                glVertex3f(xc2,h1,zc2);
                glEnd();

                xc1 = xc2, zc1 = zc2;
            }
        }
        else {
            for (int i = 1; i <= slices + 1; i++) {
                xc2 = radius * sin(i * alpha);
                zc2 = radius * cos(i * alpha);
                xc4 = radius2 * sin(i * alpha);
                zc4 = radius2 * cos(i * alpha);
                cor1 = ((float) rand()) / (float) RAND_MAX;
                cor2 = ((float) rand()) / (float) RAND_MAX;

                glBegin(GL_TRIANGLES);
                glColor3f(cor1, cor2, 0.0f);
                glVertex3f(xc1, h1, zc1);
                glVertex3f(xc2, h1, zc2);
                glVertex3f(xc3, h2, zc3);
                glVertex3f(xc2, h1, zc2);
                glVertex3f(xc4, h2, zc4);
                glVertex3f(xc3, h2, zc3);
                glEnd();

                xc1 = xc2, zc1 = zc2;
                xc3 = xc4, zc3 = zc4;
            }
        }

        h1 = h2;
        radius = radius2;
    }
}
