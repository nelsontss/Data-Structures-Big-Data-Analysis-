package engine;

import li3.TADCommunity;
import javax.xml.stream.XMLStreamException;
import java.io.FileNotFoundException;
import java.util.ArrayList;

/**
 * Write a description of class GestStackOverflowMVCApp here.
 *
 * @author (your name)
 * @version (a version number or a date)
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

        model = createDate("xml/");


        GestStackOverflowView view = new GestStackOverflowView();
        GestStackOverflowController control = new GestStackOverflowController();
        control.setModel(model);
        control.setView(view);

        control.startController();

        System.exit(0);

    }
}
