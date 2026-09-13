let ultimoScroll = 0;

window.addEventListener("scroll", function () {
  const header = document.querySelector("header");

  // Se o cabeçalho não existir, não faz nada (evita erros)
  if (!header) return;

  // Lê a posição atual da página
  let scrollAtual = window.scrollY || document.documentElement.scrollTop;

  // Se estivermos no topo do ecrã (ou muito perto), mostra sempre o cabeçalho
  if (scrollAtual <= 50) {
    header.classList.remove("header-hidden");
    ultimoScroll = scrollAtual;
    return;
  }

  // Se a rolagem for para BAIXO, adiciona a classe para esconder
  if (scrollAtual > ultimoScroll) {
    header.classList.add("header-hidden");
  }
  // Se a rolagem for para CIMA, remove a classe para mostrar
  else {
    header.classList.remove("header-hidden");
  }

  // Guarda a posição para comparar no próximo movimento
  ultimoScroll = scrollAtual;
});

// Lógica de envio de mensagem (Contacto)
function enviarMensagem() {
  var nome = document.getElementById("nome").value;
  var email = document.getElementById("email").value;
  var mensagem = document.getElementById("mensagem").value;
  var areaResultado = document.getElementById("resultado");

  if (nome.trim() !== "" && email.trim() !== "" && mensagem.trim() !== "") {
    areaResultado.innerText =
      "Mensagem processada! Muito obrigado pelo contacto, " + nome + ".";
    areaResultado.style.color = "#ffaa00";

    document.getElementById("nome").value = "";
    document.getElementById("email").value = "";
    document.getElementById("mensagem").value = "";
  } else {
    areaResultado.innerText =
      "Erro: Por favor, preenche todos os campos antes de enviar.";
    areaResultado.style.color = "#ff5500";
  }
}
function toggleProjetos() {
  // Seleciona todos os projetos que têm a classe 'projeto-extra'
  const projetosExtras = document.querySelectorAll(".projeto-extra");
  const btn = document.getElementById("btn-ver-mais");

  // PREVENÇÃO DE ERRO: Se não encontrar projetos extra ou o botão, para por aqui e avisa
  if (!projetosExtras || projetosExtras.length === 0 || !btn) {
    console.log(
      "Aviso: Nenhum projeto com a classe 'projeto-extra' encontrado no HTML.",
    );
    return;
  }

  // Verifica se o primeiro projeto extra está visível
  let estaVisivel = projetosExtras[0].classList.contains("mostrar");

  if (!estaVisivel) {
    // Se estiver escondido, mostra todos
    projetosExtras.forEach((projeto) => {
      projeto.classList.add("mostrar");
    });
    // Troca o texto e a setinha do botão
    btn.innerHTML = 'Ver Menos <i class="fas fa-chevron-up"></i>';
  } else {
    // Se já estiver mostrando, esconde todos
    projetosExtras.forEach((projeto) => {
      projeto.classList.remove("mostrar");
    });
    // Volta o botão ao normal
    btn.innerHTML = 'Veja Mais <i class="fas fa-chevron-down"></i>';

    // Rola a página de volta para a secção de projetos sem dar erro
    const secaoProjetos = document.getElementById("projetos");
    if (secaoProjetos) {
      secaoProjetos.scrollIntoView({ behavior: "smooth" });
    }
  }
}
