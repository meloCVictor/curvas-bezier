# 🎯 Curva Bézier de Grau 4 — Subdivisão com Algoritmo de De Casteljau

Este projeto implementa a renderização de uma **Curva Bézier de grau 4** utilizando **OpenGL** com o algoritmo de **De Casteljau** de forma **recursiva**.

O código visualiza tanto os pontos de controle quanto a construção da curva em tempo real, mostrando o processo de subdivisão até a aproximação ficar suficientemente reta.

---

## 💡 Como funciona?

A curva Bézier de grau 4 é definida pela seguinte equação matemática:

```
B(t) = (1 - t)^4 P₀ + 4(1 - t)^3 t P₁ + 6(1 - t)^2 t^2 P₂ + 4(1 - t) t^3 P₃ + t^4 P₄
```

Onde:
- `P₀, P₁, P₂, P₃, P₄` são os pontos de controle.
- `t` varia de 0 até 1, desenhando a curva.

Este programa usa o **algoritmo de De Casteljau**, que subdivide a curva em segmentos menores usando pontos médios até que cada segmento possa ser considerado "reto" o suficiente (de acordo com um valor `threshold`).

---

## 📸 O que o programa faz:

- Desenha os **pontos de controle** com cores específicas.
- Desenha as **linhas auxiliares** entre os pontos de controle.
- Aplica o algoritmo de subdivisão **De Casteljau** para traçar a curva.
- Renderiza a curva usando OpenGL.
- Usa `std::thread` e `std::chrono` para criar pausas e visualizar o processo passo a passo.

---

## ⚙️ Como compilar

Para rodar o código, é necessário ter:

- OpenGL e GLUT instalados no seu sistema.
- Compilador que suporte C++11 ou superior.

Exemplo de compilação no Linux:

```bash
g++ main.cpp -o bezier -lGL -lGLU -lglut -pthread
./bezier
```

No Windows, se estiver usando MinGW:

```bash
g++ main.cpp -o bezier.exe -lopengl32 -lfreeglut -lglu32 -pthread
bezier.exe
```

---

## 💻 Estrutura do Código

- `drawPoint`: Desenha um ponto na tela.
- `drawLine`: Desenha uma linha entre dois pontos.
- `drawControlLines`: Conecta os pontos de controle com linhas cinzas.
- `calculateMidpoint`: Calcula o ponto médio recursivo usando o algoritmo de De Casteljau.
- `subdivideBezier`: Divide a curva em duas metades, criando novos subconjuntos de pontos.
- `drawBezierRecursive`: Desenha a curva chamando subdivisões recursivas até o segmento ser considerado reto.
- `display`: Função principal de desenho.
- `main`: Inicializa a janela OpenGL e executa o programa.

---

## 🧠 Conceitos Envolvidos

- **Curva Bézier**: Técnica usada em computação gráfica para gerar curvas suaves.
- **De Casteljau**: Algoritmo recursivo que aproxima curvas Bézier de forma eficiente e estável.
- **OpenGL/GLUT**: Ferramentas de renderização gráfica.
- **Recursão**: Funções que chamam a si mesmas, até atingir uma condição de parada.

---

## ✅ Exemplo Visual

Ao rodar o programa, você verá os pontos de controle sendo desenhados em cores vivas e as subdivisões da curva sendo refinadas, até formar uma curva suave.

---

## 🤝 Licença

Este projeto é livre para uso acadêmico e didático!  
Se usar ou modificar, sinta-se à vontade para dar créditos. 🚀
