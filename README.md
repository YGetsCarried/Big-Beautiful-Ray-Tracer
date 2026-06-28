# Big Beautiful Ray Tracer

A physically-based ray tracer written from scratch in **C++**, built for fun and for the love of light simulation. Renders photorealistic scenes with diffuse, metallic, and dielectric (glass) materials, a fully configurable camera with depth-of-field, and multi-sample anti-aliasing — all output to PPM image format.

---

## Features

- **Monte Carlo path tracing** with configurable samples-per-pixel and bounce depth
- **Three material types:**
  - `lambertian` — Diffuse surfaces with Lambertian reflectance
  - `metal` — Reflective surfaces with adjustable fuzz factor
  - `dielectric` — Glass/transparent materials using Schlick's approximation for reflectance
- **Physically-based camera model:**
  - Adjustable vertical field of view (`vfov`)
  - Look-from / look-at / up-vector positioning
  - Configurable defocus blur (depth-of-field) via defocus angle and focus distance
- **Anti-aliasing** via random stratified sampling within each pixel
- **PPM image output** written directly to `image.ppm`
- **Progress logging** to `stderr` — scanlines remaining printed to console during render

---

## Project Structure

```
Big-Beautiful-Ray-Tracer/
├── CMakeLists.txt
└── src/
    ├── main.cpp           # Scene definition and render entry point
    ├── camera.h           # Camera model, ray generation, render loop
    ├── material.h         # Lambertian, Metal, Dielectric materials
    ├── sphere.h           # Sphere geometry and ray-sphere intersection
    ├── hittable.h         # Abstract hittable interface and hit_record
    ├── hittable_lists.h   # Scene container (list of hittables)
    ├── ray.h              # Ray class (origin + direction)
    ├── vec3.h             # 3D vector math (dot, cross, reflect, refract, etc.)
    ├── color.h            # Color utilities and PPM output
    ├── interval.h         # Scalar interval [min, max] utilities
    ├── rtweekend.h        # Constants, random number generation, shared includes
    └── all.h              # Convenience aggregate header
```

---

## Build & Run

### Requirements

- CMake ≥ 3.10
- A C++17-compatible compiler (GCC, Clang, MSVC)

### Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Run

```bash
./ray_tracer
```

This writes the rendered image to `image.ppm` in the current directory. Use any PPM viewer or convert with ImageMagick:

```bash
convert image.ppm output.png
```

---

## Default Scene

The default scene (defined in `main.cpp`) renders the classic "final scene" from *Ray Tracing in One Weekend* — a ground plane populated with hundreds of randomly placed small spheres (diffuse, metal, and glass), plus three large feature spheres (glass, lambertian, and polished metal). The camera is configured with:

| Parameter | Value |
|-----------|-------|
| Resolution | 1200 × 675 (16:9) |
| Samples per pixel | 10 |
| Max ray bounces | 50 |
| Vertical FOV | 20° |
| Defocus angle | 0.6° |
| Focus distance | 10.0 |

> Increasing `samples_per_pixel` dramatically improves image quality but also render time. A value of 500+ is recommended for final renders.

---

## Architecture Notes

- All geometry inherits from the abstract `hittable` class via `hit()`, making it easy to add new primitives (triangles, boxes, etc.)
- Materials are polymorphic via the `material` base class — new BRDFs can be plugged in by implementing `scatter()`
- The camera handles the full render loop, ray generation (with defocus disk sampling), and PPM file writing
- Schlick's approximation is used in `dielectric::scatter()` for physically plausible reflectance at glancing angles

---

## References & Inspiration

- [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) — Peter Shirley
- Built from scratch because it seemed very fun to make 

---

## 📄 License

MIT License — see [LICENSE](./LICENSE) for details.
