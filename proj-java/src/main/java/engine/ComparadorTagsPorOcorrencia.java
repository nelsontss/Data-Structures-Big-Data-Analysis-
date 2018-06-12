package engine;

import java.util.Comparator;
import java.util.Map;
/**
 * Comparador de pares (tag, ocorrência) por ocorrência
 * @author Grupo 48
 * @version 12/06/2018
 */
public class ComparadorTagsPorOcorrencia implements Comparator<Map.Entry<String, Integer>> {
    /**
     * Comparador de pares (tag, ocorrência) que as ordena por ordem decrescente de ocorrência
     * @param a Par 1
     * @param b Par 2
     * @return Valor >0 se a ocorrência do par 1 é menor que a do par 2, <0 se a ocorrência do par 2 é menor que a do par 1. Caso as ocorrências sejam iguais, desempata-se comparando as Strings
     */
    public int compare(Map.Entry<String,Integer> a, Map.Entry<String,Integer> b){
            if(a.getValue() == b.getValue()) {
                int x = Integer.parseInt(a.getKey());
                int y = Integer.parseInt(b.getKey());
                return Integer.compare(x,y);
            }
            else
                return -1 * a.getValue().compareTo(b.getValue());
    }
}
