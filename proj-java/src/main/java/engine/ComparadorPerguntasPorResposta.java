package engine;

import java.util.Comparator;

public class ComparadorPerguntasPorResposta implements Comparator<Pergunta> {
    public int compare (Pergunta p1, Pergunta p2){
        int r= -1 * Integer.compare(p1.getAnswerCount(), p2.getAnswerCount());
        if(r==0)
            r = -1 * p1.getID().compareTo(p2.getID());

        return r;
    }
}
