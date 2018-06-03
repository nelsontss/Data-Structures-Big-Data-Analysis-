package engine;

import java.util.Comparator;

public class ComparadorPostsPorData implements Comparator<MyPost> {
        public int compare(MyPost p1, MyPost p2){
            int r = p1.getData().compareTo(p2.getData());
            if (r == 0)
                return p1.getID().compareTo(p2.getID());
            else
                return r*-1;
        }
}
