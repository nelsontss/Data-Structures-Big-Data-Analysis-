package engine;

import java.util.Comparator;

public class ComparadorRespostasPorPont implements Comparator<Resposta> {
    public int compare(Resposta r1, Resposta r2){
        int r = Double.compare(r1.getPont(),r2.getPont());
        if(r==0)
            return -1 * r1.getID().compareTo(r2.getID());
        else
            return r*-1;
    }
}
