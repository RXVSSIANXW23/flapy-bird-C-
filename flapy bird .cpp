<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<style>
    body { background: #111; color: #fff; text-align: center; font-family: sans-serif; margin: 0; padding: 5px; }
    canvas { background: #70c5ce; border: 3px solid #fff; display: block; margin: 5px auto; }
    h3 { color: #f7e61a; margin: 2px 0; font-size: 14px; }
</style>
</head>
<body>
<h3>🐦 FLAPPY COMPACTO 🐦</h3>
<canvas id="flappy" width="280" height="240"></canvas>

<script>
// VARIABLES CLÁSICAS CON VAR (Compatibilidad 100% con Squarefree)
var canvas = document.getElementById("flappy");
var ctx = canvas.getContext("2d");

var birdY = 100;
var birdX = 50;
var gravity = 0.4;
var velocity = 0;
var jump = -6;
var birdSize = 10;

var pipeX = 300;
var pipeY = 60;
var pipeWidth = 40;
var pipeGap = 85; 
var score = 0;

var gameStarted = false;
var gameOver = false;

// Evento de teclado clásico
document.onkeydown = function(e) {
    var key = e.keyCode || e.which;
    if (key === 32) { // 32 es la barra espaciadora
        if (gameOver) {
            // Reiniciar valores
            birdY = 100;
            velocity = 0;
            pipeX = 300;
            pipeY = Math.floor(Math.random() * 80) + 20;
            score = 0;
            gameOver = false;
            gameStarted = false;
        } else {
            gameStarted = true;
            velocity = jump;
        }
    }
};

function loop() {
    // 1. LÓGICA
    if (gameStarted && !gameOver) {
        velocity += gravity;
        birdY += velocity;

        // Mover tubo
        pipeX -= 2;

        // Si el tubo sale de la pantalla, reiniciar su posición
        if (pipeX + pipeWidth < 0) {
            pipeX = canvas.width;
            pipeY = Math.floor(Math.random() * 80) + 20; // Altura aleatoria
            score++;
        }

        // Colisión con el suelo o techo
        if (birdY + birdSize > canvas.height || birdY - birdSize < 0) {
            gameOver = true;
        }

        // Colisión matemática con los tubos
        if (birdX + birdSize > pipeX && birdX - birdSize < pipeX + pipeWidth) {
            if (birdY - birdSize < pipeY || birdY + birdSize > pipeY + pipeGap) {
                gameOver = true;
            }
        }
    }

    // 2. RENDERIZADO (DIBUJO)
    // Fondo azul cielo
    ctx.fillStyle = "#70c5ce";
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    // Tubo superior
    ctx.fillStyle = "#73bf2e";
    ctx.fillRect(pipeX, 0, pipeWidth, pipeY);
    ctx.strokeStyle = "#000";
    ctx.strokeRect(pipeX, 0, pipeWidth, pipeY);

    // Tubo inferior
    ctx.fillRect(pipeX, pipeY + pipeGap, pipeWidth, canvas.height);
    ctx.strokeRect(pipeX, pipeY + pipeGap, pipeWidth, canvas.height);

    // Pájaro amarillo simplificado
    ctx.fillStyle = "#f7e61a";
    ctx.beginPath();
    ctx.arc(birdX, birdY, birdSize, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();

    // Pico naranja
    ctx.fillStyle = "#ff7700";
    ctx.beginPath();
    ctx.moveTo(birdX + birdSize, birdY - 2);
    ctx.lineTo(birdX + birdSize + 5, birdY + 1);
    ctx.lineTo(birdX + birdSize, birdY + 4);
    ctx.fill();

    // Marcador de puntos
    ctx.fillStyle = "#fff";
    ctx.font = "bold 18px sans-serif";
    ctx.textAlign = "center";
    ctx.fillText("PUNTOS: " + score, canvas.width / 2, 25);

    // Mensajes en pantalla
    if (!gameStarted) {
        ctx.fillStyle = "rgba(0,0,0,0.5)";
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        ctx.fillStyle = "#fff";
        ctx.font = "12px sans-serif";
        ctx.fillText("PRESIONA ESPACIO PARA EMPEZAR", canvas.width / 2, canvas.height / 2);
    }

    if (gameOver) {
        ctx.fillStyle = "rgba(0,0,0,0.7)";
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        ctx.fillStyle = "#ff3333";
        ctx.font = "bold 16px sans-serif";
        ctx.fillText("GAME OVER", canvas.width / 2, canvas.height / 2 - 5);
        ctx.fillStyle = "#fff";
        ctx.font = "10px sans-serif";
        ctx.fillText("ESPACIO PARA REINICIAR", canvas.width / 2, canvas.height / 2 + 15);
    }
}

// Bucle de tiempo estándar antiguo (60 actualizaciones por segundo)
setInterval(loop, 1000 / 60);
</script>
</body>
</html>
