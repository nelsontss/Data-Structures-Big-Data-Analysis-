package engine;

import java.util.Comparator;
/**
 * Comparador de respostas por número de votos
 * @version 12/06/2018
 */
public class ComparadorRespostasVotos implements Comparator<Resposta> {
    /**
     * Comparador de respostas que ordena-as por ordem descrescente de score(votos)
     * @param r1 Resposta 1
     * @param r2 Resposta 2
     * @return Valor >0 se o score do post 1 é menor que o do post 2, <0 se o score do post 2 é menor que o do post 1. Caso os scores sejam iguais, desempata-se comparando os IDs lexicograficamente por ordem inversa
     */
    public int compare(Resposta r1, Resposta r2){
        int r= Integer.compare(r1.getScore(), r2.getScore());
        if (r==0)
            return r1.getID().compareTo(r2.getID());
        else
            return r*-1;

    }
}
