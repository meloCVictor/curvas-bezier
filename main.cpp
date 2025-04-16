#include <GL/glut.h>        // Inclui a biblioteca OpenGL (GLUT) que permite desenhar gr�ficos na tela.
#include <cmath>            // Inclui fun��es matem�ticas, como raiz quadrada e valor absoluto.
#include <iostream>         // Permite mostrar mensagens no terminal (n�o usado aqui, mas inclu�do).
#include <thread>           // Permite pausar a execu��o do programa por um tempo.
#include <chrono>           // Usado junto com thread para definir o tempo da pausa.
#include <vector>           // Permite criar listas din�micas (vetores) que podem crescer e diminuir.


// Estrutura de ponto
struct Point {
    float x, y; // x = posi��o horizontal, y = posi��o vertical
};


// Desenha um ponto com cor personalizada
void drawPoint(Point p, float r, float g, float b) {
    glColor3f(r, g, b);      // Define a cor do ponto (R=vermelho, G=verde, B=azul).
    glPointSize(8);          // Define o tamanho do ponto.
    glBegin(GL_POINTS);      // Inicia o desenho de um ponto.
        glVertex2f(p.x, p.y);// Define as coordenadas do ponto.
    glEnd();                 // Termina o desenho.
}


// Desenha uma linha entre dois pontos com cor personalizada
void drawLine(Point a, Point b, float r, float g, float b_) {
    glColor3f(r, g, b_);     // Define a cor da linha.
    glBegin(GL_LINES);       // Inicia o desenho de uma linha.
        glVertex2f(a.x, a.y);// Come�a no ponto A.
        glVertex2f(b.x, b.y);// Termina no ponto B.
    glEnd();                 // Termina o desenho.
}


// Desenha linhas auxiliares entre os pontos de controle
void drawControlLines(Point p0, Point p1, Point p2, Point p3, Point p4) {
    drawLine(p0, p1, 0.5f, 0.5f, 0.5f);  // Cinza
    drawLine(p1, p2, 0.5f, 0.5f, 0.5f);  // Cinza
    drawLine(p2, p3, 0.5f, 0.5f, 0.5f);  // Cinza
    drawLine(p3, p4, 0.5f, 0.5f, 0.5f);  // Cinza
}


// Fun��o recursiva de De Casteljau: reduz at� achar o ponto intermedi�rio
Point calculateMidpoint(const std::vector<Point>& points) {
    if (points.size() == 1) return points[0]; // Caso base: s� restou 1 ponto.

    std::vector<Point> newPoints;
    //Cria uma nova lista para guardar os pontos intermedi�rios.
    //Esse for calcula a m�dia entre cada par de pontos e adiciona na lista newPoints. Esse processo � o cora��o do algoritmo de De Casteljau.
    for (size_t i = 0; i < points.size() - 1; i++) {
        Point mid;
        mid.x = (points[i].x + points[i + 1].x) / 2;
        mid.y = (points[i].y + points[i + 1].y) / 2;
        newPoints.push_back(mid);
    }
    return calculateMidpoint(newPoints);
}

// Fun��o recursiva para subdividir o conjunto de pontos usando De Casteljau
//Essa fun��o divide a curva em duas partes: left (parte da esquerda) e right (parte da direita).
void subdivideBezier(const std::vector<Point>& controlPoints, std::vector<Point>& left, std::vector<Point>& right) {
    if (controlPoints.size() == 1) {
        left.push_back(controlPoints[0]);
        right.push_back(controlPoints[0]);
        return;
    }

    left.push_back(controlPoints.front()); // Adiciona o primeiro ponto ao lado esquerdo.
    right.push_back(controlPoints.back()); // Adiciona o �ltimo ponto ao lado direito.

    //Aqui ele salva o primeiro e o �ltimo ponto nas listas.
    std::vector<Point> nextLevel;
    for (size_t i = 0; i < controlPoints.size() - 1; i++) {
        Point mid;
        mid.x = (controlPoints[i].x + controlPoints[i + 1].x) / 2;
        mid.y = (controlPoints[i].y + controlPoints[i + 1].y) / 2;
        nextLevel.push_back(mid);
    }

    //Novamente calcula os pontos m�dios e gera um novo conjunto de pontos intermedi�rios.
    subdivideBezier(nextLevel, left, right);
}

// Fun��o recursiva para desenhar a curva B�zier
void drawBezierRecursive(Point p0, Point p1, Point p2, Point p3, Point p4, float threshold) {
    // Desenhar pontos de controle
    drawPoint(p0, 1, 0, 0);  // Vermelho
    drawPoint(p1, 0, 1, 0);  // Verde
    drawPoint(p2, 0, 0, 1);  // Azul
    drawPoint(p3, 1, 1, 0);  // Amarelo
    drawPoint(p4, 1, 0, 1);  // Roxo

    drawControlLines(p0, p1, p2, p3, p4);

    glFlush();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    // Calcula dist�ncia para saber se o segmento pode ser considerado uma reta
    //Verificando se a curva pode ser simplificada
    float dx = p4.x - p0.x;
    float dy = p4.y - p0.y;

    //Calcula a dire��o da linha reta entre o primeiro e o �ltimo ponto.
    float d1 = std::abs((p1.x - p0.x) * dy - (p1.y - p0.y) * dx);
    float d2 = std::abs((p2.x - p0.x) * dy - (p2.y - p0.y) * dx);
    float d3 = std::abs((p3.x - p0.x) * dy - (p3.y - p0.y) * dx);
    float d4 = std::abs((p4.x - p0.x) * dy - (p4.y - p0.y) * dx);

    //alcula a dist�ncia perpendicular de cada ponto de controle at� a linha reta entre p0 e p4. Se todos estiverem muito pr�ximos, � seguro desenhar uma linha no lugar da curva.
    float d = std::max(std::max(d1, d2), std::max(d3, d4)) / sqrt(dx * dx + dy * dy);


    if (d < threshold) {
        drawLine(p0, p4, 1, 0, 1);  // Desenha a linha final (rosa)
        glFlush();
        return;
    }

    // Subdivide usando a fun��o
    std::vector<Point> controlPoints = { p0, p1, p2, p3, p4 };
    std::vector<Point> left, right;
    subdivideBezier(controlPoints, left, right);

    // Chamada recursiva com novos subconjuntos
    drawBezierRecursive(left[0], left[1], left[2], left[3], left[4], threshold);
    drawBezierRecursive(right[4], right[3], right[2], right[1], right[0], threshold);
}

// Fun��o de exibi��o
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    Point p0 = {-0.8f, -0.8f};
    Point p1 = {-0.6f, 0.8f};
    Point p2 = {-0.2f, 0.6f};
    Point p3 = {0.2f, -0.6f};
    Point p4 = {0.8f, -0.8f};

    drawBezierRecursive(p0, p1, p2, p3, p4, 0.001f);

    glFlush();
}

// Fun��o principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Curva B�zier - Recurs�o com Subdivis�o De Casteljau");
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
