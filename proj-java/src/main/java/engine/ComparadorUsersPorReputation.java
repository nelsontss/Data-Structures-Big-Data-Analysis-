package engine;
import java.util.Comparator;
/**
 * Comparador de users por reputaçao.
 * @version 27/05
 */
public class ComparadorUsersPorReputation implements Comparator<myUser>
{
    @Override
    public int compare(myUser u1, myUser u2){ //decrescente
        int valor1=u1.getReputation(), valor2=u2.getReputation();
        if (valor1>valor2)
            return -1;
        if (valor1<valor2)
            return 1;
        return u1.getName().compareTo(u2.getName());
    }
}
