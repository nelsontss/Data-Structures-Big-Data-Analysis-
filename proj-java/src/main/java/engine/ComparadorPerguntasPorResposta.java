package engine;

import java.util.Comparator;

/**
 * Comparador de perguntas por número de respostas
 * @version 12/06/2018
 */
public class ComparadorPerguntasPorResposta implements Comparator<Pergunta> {
    /**
     * Comparador de perguntas que ordena por ordem descrecente por número de respostas
     * @param p1 Pergunta 1
     * @param p2 Pergunta 2
     * @return Valor >0 se a pergunta 1 tem menos respostas que a pergunta 2, <0 se a pergunta 1 tem mais respostas que a pergunta 2. Caso o número seja igual, desempata-se comparando os IDs lexicograficamente por ordem inversa
     */
    public int compare (Pergunta p1, Pergunta p2){
        int r= -1 * Integer.compare(p1.getAnswerCount(), p2.getAnswerCount());
        if(r==0)
            r = -1 * p1.getID().compareTo(p2.getID());

        return r;
    }
}
