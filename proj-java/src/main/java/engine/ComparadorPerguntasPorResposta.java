package engine;

import java.util.Comparator;

public class ComparadorPerguntasPorResposta implements Comparator<Pergunta> {
    public int compare (Pergunta p1, Pergunta p2){
        int r= Integer.compare(p1.getAnswerCount(), p2.getAnswerCount());
        if(r==0)
            return p1.getID().compareTo(p1.getID());
        else
            return r*-1;
    }
}
