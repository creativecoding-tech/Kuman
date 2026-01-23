## 🔬 Kuman | OpenFrameworks Spiral Visualization

Visualisasi generatif dengan pola spiral organik dan animasi sel yang halus. Project ini mengimplementasikan algoritma Golden Angle (137.5°) untuk menciptakan pola spiral yang terinspirasi dari alam (biji bunga matahari, tunas pinus).

[![Watch Demo](https://img.shields.io/badge/Watch-Demo-red?style=for-the-badge&logo=youtube)](https://youtu.be/q5FcSIjvfvI)

[![OpenFrameworks](https://img.shields.io/badge/OpenFrameworks-0.12.1-blue)](https://openframeworks.cc)
![C++](https://img.shields.io/badge/C++-17-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![License](https://img.shields.io/badge/License-Apache%202.0-green)

---

## 📺 Demo Video

Lihat hasilnya di YouTube: **[Kuman - Phyllotaxis Visualization](https://youtu.be/q5FcSIjvfvI)**

---

## ✨ Fitur & Teknik

- **Phyllotaxis Spiral** — Pola spiral organik berdasarkan Golden Angle (137.5°)
- **Grid Layout System** — 2D grid yang dapat bertransformasi ke mode phyllotaxis
- **Smooth Cell Animation** — Easing interpolation untuk transisi posisi yang halus
- **GPU-Accelerated Rendering** — Custom OpenGL shaders (GLSL) untuk performa tinggi
- **Three Background Modes**:
  - **Trails Mode**: Semi-transparent overlay untuk efek jejak visual
  - **Canvas Mode**: Tanpa background clear untuk melukis di canvas
  - **Normal Mode**: Background putih bersih
- **Interactive GUI Controls** — Panel kontrol real-time dengan ofxGui
- **Fibonacci Color Palette** — Warna berbasis sequence Fibonacci untuk setiap sel

---

## 🎮 Controls

| Input | Action |
| --- | --- |
| **Key 'P'** | Transform semua sel ke pola Phyllotaxis |
| **Key 'N'** | Transform semua sel ke layout Grid |
| **Key 'G'** | Tampilkan/Sembunyikan panel GUI |
| **Key 'Q'** | Keluar dari aplikasi |
| **Right Click** | Toggle visibilitas kursor |

### GUI Controls
- **[ + ] Tambah** — Naikkan ukuran sel (max 60px)
- **[ - ] Kurang** — Turunkan ukuran sel (min 5px)
- **Mode Trails** — Aktifkan efek jejak visual
- **Mode Canvas** — Mode melukis tanpa clear
- **Mode Normal** — Mode background standar

---

## 🛠️ Tech Stack

- **OpenFrameworks 0.12.1**
- **C++17**
- **OpenGL 4.6** dengan custom GLSL shaders
- **Visual Studio 2022** (v143 toolset)
- **ofxGui** addon untuk kontrol UI
- **Phyllotaxis Algorithms**
- **Golden Ratio (φ = 1.618...)**

---

## 📦 Installation

### Prerequisites

1. Install **OpenFrameworks** untuk Windows dari [openframeworks.cc](https://openframeworks.cc)
2. Install **Visual Studio 2022** dengan workload "Desktop development with C++"

### Setup

```bash
# Clone repository ini
git clone https://github.com/creativecoding-tech/Kuman.git

# Jalankan OpenFrameworks Project Generator
# Buka: openFrameworks/apps/projectGenerator/projectGenerator.exe

# Import project yang sudah diclone
# 1. Click "Import" pada Project Generator
# 2. Navigate ke folder Kuman yang sudah diclone
# 3. Select folder dan klik "Select Current Folder"
# 4. Click "Update" atau "Generate"

# Buka Visual Studio
# Double-click: Kuman.sln

# Build & Run
# Press F5 atau klik "Local Windows Debugger"
```

---

## 🧬 Mathematics Behind

### Phyllotaxis Formula

Pola phyllotaxis dalam alam mengikuti sudut emas untuk distribusi efisien:

```
angle = n × 137.5° (golden angle)
radius = c × √n
x = center_x + radius × cos(angle)
y = center_y + radius × sin(angle)
```

### Fibonacci Sequence

Setiap sel memiliki warna berdasarkan sequence Fibonacci:

```
F(n) = F(n-1) + F(n-2)
dengan F(0) = 0, F(1) = 1
```

### Shader Animation

Vertex shader menghandle:
- Posisi interpolasi dengan `mix(startPos, targetPos, progress)`
- Transformasi lokal (rotasi & scaling)
- GPU-based position calculation untuk smooth 60 FPS

---

## 📁 Project Structure

```
Kuman/
├── src/
│   ├── main.cpp           # Entry point aplikasi
│   ├── ofApp.cpp/h        # Main application class
│   └── Cell.cpp/h         # Cell class (animasi & rendering)
├── bin/
│   └── data/
│       └── shadersGL3/    # OpenGL shaders
│           ├── shader.vert # Vertex shader
│           └── shader.frag # Fragment shader
├── dll/                   # OF dependencies
├── obj/                   # Intermediate files (gitignored)
└── Kuman.sln/.vcxproj     # Visual Studio project files
```

---

## 🎯 Purpose

Project ini adalah bagian dari eksplorasi **Creative Coding** dan pembelajaran:

- 🔬 Eksperimen visual algorithms dan geometric patterns
- 🎨 Belajar shader programming dengan GLSL
- ⚡ Implementasi GPU-accelerated rendering
- 📚 Memahami matematika dalam visual programming
- 🌿 Menyelami pola-pola organik dari alam

---

## 🚀 Performance

Dengan optimasi OpenGL shaders dan modern C++:
- **Solid 60 FPS** pada resolusi 1920x1080
- **GPU-based rendering** untuk ribuan sel
- **Smooth easing** tanpa lag
- **Hardware acceleration** penuh

---

## 🤝 Contributing

Ide, saran, dan improvement sangat welcome! Feel free to share your experiments!

---

## 📄 License

This project is licensed under the **Apache License 2.0** - see the LICENSE file for details.

---

## 🙏 Credits & References

- **OpenFrameworks** - Creative coding framework
- **Nature** - Phyllotaxis patterns dari tumbuhan 🌻
- **VirusOf** - Sister project untuk performance comparison

---

## 🔗 Links

- **YouTube Demo**: [Kuman - Phyllotaxis Visualization](https://youtu.be/q5FcSIjvfvI)
- **OpenFrameworks**: [openframeworks.cc](https://openframeworks.cc)

---

**Made with ❤️ for learning and creative exploration**
