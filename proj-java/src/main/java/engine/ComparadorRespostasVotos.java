package engine;

import java.util.Comparator;

public class ComparadorRespostasVotos implements Comparator<Resposta> {
    public int compare(Resposta r1, Resposta r2){
        int r= Integer.compare(r1.getScore(), r2.getScore());
        if (r==0)
            return r1.getID().compareTo(r2.getID());
        else
            return r*-1;

    }
}
