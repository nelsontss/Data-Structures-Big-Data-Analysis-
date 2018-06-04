package engine;

import java.util.ArrayList;
import java.util.List;

public class GestStackOverflowView {
    private List<String> menus;

    public GestStackOverflowView() {
        menus = initMenus();
    }

    public List<String> initMenus() {
        List<String> r = new ArrayList<>();
        r.add(this.getMainMenu());

        return r;
    }

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

    public String getMainMenu() {
        StringBuilder sb = new StringBuilder();
        sb.append("\n--------------------------------------------");
        sb.append("\n-                                          -");
        sb.append("\n-  Bem Vindo ao StackOverflow Researcher!  -");
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
        sb.append("\n-                                          -");
        sb.append("\n--------------------------------------------");



        return sb.toString();
    }
}