package engine;

import java.util.Comparator;
/**
 * Comparador de respostas por pontuação
 * @author Grupo 48
 * @version 12/06/2018
 */
public class ComparadorRespostasPorPont implements Comparator<Resposta> {
    /**
     * Comparador de respostas que as ordena por ordem decrescente de pontuação
     * @param r1 Resposta 1
     * @param r2 Resposta 2
     * @return Valor >0 se a pontuação do post 1 é menor do que a do post 2, <0 se a pontuação do post 2 é menor do que a do post 1. Caso as pontuações sejam iguais, desempata-se comparando os IDs lexicograficamente por ordem inversa
     */
    public int compare(Resposta r1, Resposta r2){
        int r = Double.compare(r1.getPont(),r2.getPont());
        if(r==0)
            return -1 * r1.getID().compareTo(r2.getID());
        else
            return r*-1;
    }
}
