function enviarMensagem() {
    var nome = document.getElementById("nome").value;
    var email = document.getElementById("email").value;
    var mensagem = document.getElementById("mensagem").value;
    var areaResultado = document.getElementById("resultado");

    if (nome.trim() !== "" && email.trim() !== "" && mensagem.trim() !== "") {
        areaResultado.innerText = "Mensagem processada! Muito obrigado pelo contato, " + nome + ".";
        areaResultado.style.color = "#ffaa00"; 
        
        document.getElementById("nome").value = "";
        document.getElementById("email").value = "";
        document.getElementById("mensagem").value = "";
    } else {
        areaResultado.innerText = "Erro: Por favor, preencha todos os campos antes de enviar.";
        areaResultado.style.color = "#ff5500"; 
    }
}