#include "draw.hpp"
#include "math.hpp"
#include "otto-gfx/gfx.hpp"
#include "display.hpp"

#include <glm/gtx/rotate_vector.hpp>

namespace otto {

void drawProgressArc(const Display &display, float progress) {
  float r = display.bounds.size.x * 0.5f - 8.0f;
  float a = HALF_PI + progress * TWO_PI;

  ScopedMask mask(display.bounds.size);
  ScopedFillRule fr(VG_NON_ZERO);
  beginMask();

  beginPath();
  arc(vec2(), vec2(r * 2.0f), a, HALF_PI);
  strokeWidth(3.0f);
  strokeCap(VG_CAP_BUTT);
  stroke();

  beginPath();
  circle(0, r, 3);
  circle(glm::rotate(vec2(r, 0), a), 3);
  fill();

  endMask();

  beginPath();
  rect(display.bounds.size * -0.5f, display.bounds.size);
  fill();
}

void fillTextCenteredWithSuffix(const std::string &text, const std::string &suffix, float textSize,
                                float suffixSize) {
  ScopedTransform xf;

  fontSize(textSize);
  auto textBounds = getTextBounds(text);
  fontSize(suffixSize);
  auto suffixBounds = getTextBounds(suffix);

  textAlign(ALIGN_LEFT | ALIGN_BASELINE);
  translate(-0.5f * (textBounds.size.x + suffixBounds.size.x), 0);
  fontSize(textSize);
  fillText(text);
  translate(textBounds.size.x, 0);
  fontSize(suffixSize);
  fillText(suffix);
}

} // otto
