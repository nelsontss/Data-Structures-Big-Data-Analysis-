package engine;

import java.util.Comparator;
/**
 * Comparador de posts por data
 * @author Grupo 48
 * @version 12/06/2018
 */
public class ComparadorPostsPorData implements Comparator<MyPost> {
    /**
     * Comparador de posts que os ordena por ordem decrescente de data
     * @param p1 Post 1
     * @param p2 Post 2
     * @return Valor >0 se a data do post 1 é anterior à do post 2, <0 se a data do post 2 é anterior à do post 1. Caso as datas sejam iguais, desempata-se comparando os IDs lexicograficamente por ordem inversa
     */
    public int compare(MyPost p1, MyPost p2){
            int r = p1.getData().compareTo(p2.getData());
            if (r == 0)
                return -1*p1.getID().compareTo(p2.getID());
            else
                return -1*r;
        }
}
