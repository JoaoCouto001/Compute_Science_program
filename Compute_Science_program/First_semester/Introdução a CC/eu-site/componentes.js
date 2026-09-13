fetch("componentes/github-card.html") // Certifique-se de que o arquivo se chama github-card.html
    .then(resposta => {
        if (!resposta.ok) throw new Error("Erro ao carregar o arquivo HTML");
        return resposta.text();
    })
    .then(dados => {
        document.getElementById("github-container").innerHTML = dados;
    })
    .catch(erro => console.error("Erro no Fetch:", erro));