package engine;

import li3.TADCommunity;
import javax.xml.stream.XMLStreamException;
import java.io.FileNotFoundException;
import java.util.ArrayList;

/**
 * Classe que permite iniciar o programa
 *
 * @author Grupo 48
 * @version 12/06/2018
 */
public class GestStackOverflowMVCApp
{
    private static TADCommunity createDate(String path) {
        GestStackOverflowModel estado = new GestStackOverflowModel();
        estado.load(path);
        
        
        return estado;
    }


    public static void main(String[] args){
        
        TADCommunity model;
        model = createDate(args[0]);


        GestStackOverflowView view = new GestStackOverflowView();
        GestStackOverflowController control = new GestStackOverflowController();
        control.setModel(model);
        control.setView(view);

        control.startController();

        System.exit(0);

    }
}
