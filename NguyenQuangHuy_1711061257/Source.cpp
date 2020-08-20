#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
//Hằng quy trạng thái của tay và chân
const char BACKWARD_STATE = 0;
const char FORWARD_STATE = 1;
//Index qui ước cho mảng (góc xoay của tay và chân)
const char LEFT = 0;
const char RIGHT = 1;
/* Trạng thái di chuyển hiện tại của tay và chân (BACKWARD_STATE/FORWARD_STATE)*/

char legStates[2];
char armStates[2];
// GÓC xoay hiện tại của tay  và chân
float legAngles[2];
float armAngles[2];
// GÓC xoay hiện tại của toàn bộ robot
float angle;

void DrawCube(float xaPos, float yPos, float zPos);
void DrawArm(float xPos, float yPos, float zPos);
void DrawHead(float xPos, float yPos, float zPos);
void DrawTorso(float xPos, float yPos, float zPos);
void DrawLeg(float xPos, float yPos, float zPos);
void DrawRobot(float xPos, float yPos, float zPos);
void Prepare();
void Display();
void Init();
void Reshape(int width, int height);
void Idle();

void DrawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix(); /*Lưu trạng thái biến đổi hiện tại vào stack*/
	glTranslatef(xPos, yPos, zPos);
	glBegin(GL_QUADS);
	// Vẽ mặt trên
	glNormal3d(0, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	// Vẽ mặt trước
	glNormal3d(0, 0, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	// Vẽ mặt bên phải
	glNormal3d(1, 0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	//Vẽ mặt bên trái
	glNormal3d(-1, 0, 0);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	//Vẽ mặt dưới
	glNormal3d(0, -1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	// Vẽ mặt sau
	glNormal3d(0, 0, -1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glEnd();
	glPopMatrix();// Quay lại trạng thái biến đổi đã lưu
}

void DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();// Tô màu đỏ
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(xPos, yPos, zPos);// Kích thước 1x4x1
	glScalef(1.0f, 4.0f, 1.0f);
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix(); // Tô màu trắng
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(xPos, yPos, zPos); // Kích thước 2x2x2
	glScalef(2.0f, 2.0f, 2.0f);
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void DrawTorso(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f); // Tô màu xanh
	glTranslatef(xPos, yPos, zPos);
	glScalef(3.0f, 5.0f, 2.0f); //Kích thước 3x5x2
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f); //Tô màu vàng
	glTranslatef(xPos, yPos, zPos);
	glScalef(1.0f, 5.0f, 1.0f);//Kích thước 1x5x1
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void DrawRobot(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos); // Tọa độ vẽ robot
	// Vẽ phần đầu và phần thân
	DrawHead(1.0f, 2.0f, 0.0f);
	DrawTorso(1.5f, 0.0f, 0.0f);
	/*Di chuyển cánh tay trái và xoay cánh tay để tạo hiệu ứng đang bước đi*/


	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(armAngles[LEFT], 1.0f, 0.0f, 0.0f);
	DrawArm(2.5f, 0.0f, -0.5f);
	glPopMatrix();
	/*Di chuyển cánh tay phải và xoay cánh tay để tạo hiệu ứng đang bước đi*/

	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(armAngles[RIGHT], 1.0f, 0.0f, 0.0f);
	DrawArm(-1.5f, 0.0f, -0.5f);
	glPopMatrix();
	/*Di chuyển chân trái và xoay chân để tạo hiệu ứng đang bước đi*/

	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(legAngles[LEFT], 1.0f, 0.0f, 0.0f);
	DrawLeg(-0.5f, -5.0f, -0.5f);
	glPopMatrix();
	/* Di chuyển chân phải và xoay chân để tạo hiệu ứng đang bước đi*/
	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(legAngles[RIGHT], 1.0f, 0.0f, 0.0f);
	DrawLeg(1.5f, -5.0f, -0.5f);
	glPopMatrix();
}

void Prepare()
{
	/*Nếu tay/chân đang di chuyển về phía trước thì tăng tốc xoay,ngược lại (di chuyển về phía sau) thì giảm góc xoay*/

	for (char side = 0; side < 2; side++) {
		// góc xoay tay
		if (armStates[side] == FORWARD_STATE)
			armAngles[side] += 0.1f;
		else
			armAngles[side] -= 0.1f;
		// Thay đổi trang thái góc xoay
		if (armAngles[side] >= 15.0f)
			armStates[side] = BACKWARD_STATE;
		else if (armAngles[side] <= -15.0f)
			armStates[side] = FORWARD_STATE;
		// Góc xoay cho chân
		if (legStates[side] == FORWARD_STATE)
			legAngles[side] += 0.1f;
		else
			legAngles[side] -= 0.1f;
		// Thay đổi trạng thái góc xoay
		if (legAngles[side] >= 15.0f)
			legStates[side] = BACKWARD_STATE;
		else if (legAngles[side] <= -15.0f)
			legStates[side] = FORWARD_STATE;
	}
}

void Display()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	angle = angle + 0.05f; // Tăng góc xoay rôbot
	if (angle >= 360.0f)// Nếu xcay đủ vòng,reset góc xoay
		angle = 0.0f;

	glPushMatrix();
	// Xoay robot quanh trục y
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	Prepare();
	DrawRobot(0.0f, 0.0f, 0.0f); // Vẽ robot
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void Init()
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//Màu ánh sáng ambient
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	//Màu ánh sáng diffuse
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//Vị trí nguồn sáng
	GLfloat lightPos[] = { 25.0f, 25.0f, 25.0f, 0.0f };
	//Hướng chiếu sáng
	GLfloat spotDir[] = { 0.0, 0.0, 0.0, 0.0 };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// Gán giá trị mặc định ban đầu cho robot
	angle = 0.0f;
	armAngles[LEFT] = 0.0;
	armAngles[RIGHT] = 0.0;
	legAngles[LEFT] = 0.0;
	legAngles[RIGHT] = 0.0;
	armStates[LEFT] = FORWARD_STATE;
	armStates[RIGHT] = BACKWARD_STATE;
	legStates[LEFT] = FORWARD_STATE;
	legStates[RIGHT] = BACKWARD_STATE;
}

void Reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 1.0, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Idle()
{
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 800);
	glutCreateWindow("ROBOT_01");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	Init();
	glutMainLoop();
	return 0;
}