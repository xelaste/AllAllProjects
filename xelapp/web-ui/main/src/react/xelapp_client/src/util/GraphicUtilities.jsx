const arrowLength = 5;
const arrowBase = arrowLength * Math.PI / 9

function drawCircle(_2DGraphics, data) {
    const context = _2DGraphics;
    context.beginPath();
    context.arc(data.center.X, data.center.Y, data.radius, 0, 2 * Math.PI, false);
    if (data.style) {
        if (data.style.color) {
            context.fillStyle = data.style.color;
            context.fill();
        }
        if (data.style.lineWidth) {
            context.lineWidth = data.style.lineWidth;
        }
        if (data.style.strokeStyle) {
            context.strokeStyle = data.style.strokeStyle;
        }

    }
    context.stroke();
    context.closePath();
    if (data.text) {
        if (data.style && data.style.font) {
            context.font = data.style.font;
        }

        if (data.textColor) {
            context.fillStyle = data.textColor
        }
        context.beginPath();
        context.fillText(data.text, data.center.X - data.radius / 2, data.center.Y + 3, data.radius * 2);
        context.stroke();
      context.closePath();
    }
}

function drawArrow(_2dgraphics, data) {
    const x0 = data.peak.X;
    const y0 = data.peak.Y;
    const xb = x0 - arrowLength * data.cosa;
    const yb = y0 - arrowLength * data.sina;
    const y1 = yb + arrowBase * data.cosa;
    const x1 = xb - arrowBase * data.sina;
    const y2 = yb - arrowBase * data.cosa;
    const x2 = xb + arrowBase * data.sina;
    _2dgraphics.beginPath();
    _2dgraphics.moveTo(x0, y0);
    _2dgraphics.lineTo(x1, y1);
    _2dgraphics.lineTo(x2, y2);
    _2dgraphics.strokeStyle = data.strokeStyle;
    _2dgraphics.fillStyle = data.fillStyle;
    _2dgraphics.stroke();
    _2dgraphics.fill()
    _2dgraphics.closePath();
}

function halton(index, base) {
    let result = 0;
    let invBase = 1.0 / base;
    let frac = 1;
    while (index > 0) {
        frac *= invBase;
        result += frac * (parseInt(index) % parseInt(base));
        index /= base;
    }
    return result;
}

// Generate Halton 2D point sequence.
function halton2D(index, base1, base2, range) {
    let HaltonX = halton(index, base1);
    let HaltonY = halton(index, base2);
    let x = HaltonX * range.width;
    let y = HaltonY * range.height;
    return [x, y];
}

export { drawCircle, drawArrow, halton2D };