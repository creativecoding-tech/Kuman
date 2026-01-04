#version 150

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec4 color;

out vec4 vColor;

// Uniforms dari OF app
uniform vec2 startPos;
uniform vec2 targetPos;
uniform float progress;

// Transformasi Lokal (Wiggle Curve)
uniform float uScale;       // default 1.0
uniform float uRotate;      // default 0.0
uniform vec2 uCenterOffset; // Offset lokal (misal size/2)

void main()
{
    vColor = color;

    // 1. ROTASI & SCALE (Manual 2D Matrix)
    // Rotate di sekitar (0,0)
    float c = cos(uRotate);
    float s = sin(uRotate);
    
    // Matriks rotasi
    // | c  -s |
    // | s   c |
    float rx = position.x * c - position.y * s;
    float ry = position.x * s + position.y * c;

    // Apply SCALING
    rx *= uScale;
    ry *= uScale;

    // Bentuk posisi lokal yang sudah di-transform
    vec4 localPos = vec4(rx, ry, position.z, position.w);

    // 2. CENTER OFFSET (Geser agar pivot di tengah)
    localPos.x += uCenterOffset.x;
    localPos.y += uCenterOffset.y;

    // 3. INTERPOLASI POSISI CELL (Global)
    float cellX = mix(startPos.x, targetPos.x, progress);
    float cellY = mix(startPos.y, targetPos.y, progress);

    // 4. POSISI AKHIR = Transform Lokal + Posisi Cell
    vec4 finalPos = localPos + vec4(cellX, cellY, 0.0, 0.0);

    // 5. KE SCREEN SPACE
    gl_Position = modelViewProjectionMatrix * finalPos;
}
