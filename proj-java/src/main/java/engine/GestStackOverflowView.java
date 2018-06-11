package engine;

import java.util.ArrayList;
import java.util.List;

public class GestStackOverflowView {
    private List<String> menus;

    /**
     * Função que inicia os menus
     */
    public GestStackOverflowView() {
        menus = initMenus();
    }

    /**
     * Função que adiciona o main menu
     * @return Lista com os menus
     */
    public List<String> initMenus() {
        List<String> r = new ArrayList<>();
        r.add(this.getMainMenu());

        return r;
    }

    /**
     * Início do menu da query 1
     * @return String que inicia o menu da query 1
     */
    public String getInfoFromPostMenu(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-          Query 1 - infoFromPost          -");
        sb.append("\n-  Dado o id de um post obter a o seu      -");
        sb.append("\n-  titulo ou da sua respetiva pergunta,    -");
        sb.append("\n-  e o nome do autor.                      -");
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");



        return sb.toString();
    }

    /**
     * Início do menu da query 2
     * @return String que inicia o menu da query 2
     */
    public String getTopMostActiveMenu(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-          Query 2 - topMostActive         -");
        sb.append("\n-  Dado um numero N, devolve os N users    -");
        sb.append("\n-  com mais posts.                         -");
        sb.append("\n-                                          -");
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");



        return sb.toString();
    }
    /**
     * Início do menu da query 3
     * @return String que inicia o menu da query 3
     */
    public String getTotalPostsMenu(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-          Query 3 - totalPosts            -");
        sb.append("\n-  Devolve o numero de perguntas e         -");
        sb.append("\n-  respostas, num dado intervalo de tempo. -");
        sb.append("\n-                                          -");
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");

        return sb.toString();
    }

    /**
     * Início do menu da query 4
     * @return String que inicia o menu da query 4
     */
    public String getQuestionsWithTagMenu(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-          Query 4 - questionsWithTag      -");
        sb.append("\n-  Devolve uma lista com as peguntas que   -");
        sb.append("\n-  contêm a tag indicada, e estao no       -");
        sb.append("\n-  intervalo de tempo indicado.            -");
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");

        return sb.toString();
    }

    /**
     * Início do menu da query 5
     * @return String que inicia o menu da query 5
     */
    public String getUserInfoMenu(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-          Query 5 - getUserInfo           -");
        sb.append("\n-  Dado um qualquer id de um utilizador    -");
        sb.append("\n-  esta query devolve a informaçao sobre   -");
        sb.append("\n-  esse user e os seus ultimos 10 posts.   -");
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");

        return sb.toString();
    }
    /**
     * Início do menu da query 6
     * @return String que inicia o menu da query 6
     */
    public String getMostVotedAnswersMenu(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-          Query 6 - mostVotedAnswers      -");
        sb.append("\n-  Dado um intervalo de tempo esta query   -");
        sb.append("\n-  devolve as N perguntas com mais votos.  -");
        sb.append("\n-                                          -");
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");

        return sb.toString();
    }
    /**
     * Início do menu da query 7
     * @return String que inicia o menu da query 7
     */
    public String getMostAnsweredQuestionsMenu(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-         Query 7 - mostAnsweredQuestions  -");
        sb.append("\n-  Dado um intervalo de tempo esta query   -");
        sb.append("\n-  devolve as N perguntas com mais         -");
        sb.append("\n-  respostas.                              -");
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");

        return sb.toString();
    }
    /**
     * Início do menu da query 8
     * @return String que inicia o menu da query 8
     */
    public String getContainsWordMenu(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-          Query 8 - containsWord          -");
        sb.append("\n-  Devolve as N peguntas cujos titulos     -");
        sb.append("\n-  contêm a palavra passada como           -");
        sb.append("\n-  argumento.                              -");
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");

        return sb.toString();
    }
    /**
     * Início do menu da query 10
     * @return String que inicia o menu da query 10
     */
    public String getBetterAnswerMenu(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-          Query 10 - betterAnswer         -");
        sb.append("\n-  Dado o id de uma pergunta devolve a     -");
        sb.append("\n-  melhor resposta.                        -");
        sb.append("\n-                                          -");
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");

        return sb.toString();
    }
    /**
     * Início do menu da query 9
     * @return String que inicia o menu da query 9
     */
    public String getBothParticipatedMenu(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-          Query 9 - betterAnswer          -");
        sb.append("\n-  Dados 2 ids devolve as N perguntas em   -");
        sb.append("\n-  que esses 2 utilizadores participaram.  -");
        sb.append("\n-                                          -");
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");

        return sb.toString();
    }
    /**
     * Início do menu da query 11
     * @return String que inicia o menu da query 11
     */
    public String getMostUsedBestRepMenu(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-          Query 11 - mostUsedBestRep      -");
        sb.append("\n-  Dado um intervalo de tempo devolve as   -");
        sb.append("\n-  N tags mais usadas pelos N users com    -");
        sb.append("\n-  mais reputaçao.                         -");
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");

        return sb.toString();
    }
    /**
     * Início do main menu
     * @return String que inicia o main menu
     */
    public String getMainMenu() {
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-  Bem Vindo ao StackOverflow Researcher!  -");
        sb.append("\n-          Opçao -1- sair                  -");
        sb.append("\n-          Opçao 0 - load                  -");
        sb.append("\n-          Opçao 1 - infoFromPost          -");
        sb.append("\n-          Opçao 2 - topMostActive         -");
        sb.append("\n-          Opçao 3 - totalPosts            -");
        sb.append("\n-          Opçao 4 - questionsWithTag      -");
        sb.append("\n-          Opçao 5 - getUserInfo           -");
        sb.append("\n-          Opçao 6 - mostVotedAnswers      -");
        sb.append("\n-          Opçao 7 - mostAnsweredQuestions -");
        sb.append("\n-          Opçao 8 - containsWord          -");
        sb.append("\n-          Opçao 9 - bothParticipated      -");
        sb.append("\n-          Opçao 10- betterAnswer          -");
        sb.append("\n-          Opçao 11- mostUserBestRep       -");
        sb.append("\n-          Opçao 12- clear                 -");
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");



        return sb.toString();
    }
}