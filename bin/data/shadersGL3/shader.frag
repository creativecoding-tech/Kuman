#version 150

uniform int isGold;  // 1=Gold, 0=Black, 2=Custom/Fibonacci, -1=Curve
uniform vec4 uCurveColor; // Warna manual dari C++ untuk Curve atau Fibonacci Cell
in vec4 vColor;

out vec4 outputColor;

void main()
{
    if (isGold == -1 || isGold == 2) {
        // Mode Curves (-1) atau Fibonacci Cell (2): Gunakan warna manual yang dikirim via Uniform
        outputColor = uCurveColor;
    } else {
        // Mode Cell: Gold atau Black
        vec4 goldColor = vec4(1.0, 0.765, 0.314, 0.275);
        vec4 blackColor = vec4(0.0, 0.0, 0.0, 1.0);

        if (isGold == 1) {
            outputColor = goldColor;
        } else {
            outputColor = blackColor;
        }
    }
}
