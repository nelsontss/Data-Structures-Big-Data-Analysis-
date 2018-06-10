package engine;

import java.util.Comparator;
import java.util.Map;

public class ComparadorTagsPorOcorrencia implements Comparator<Map.Entry<String, Integer>> {
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
